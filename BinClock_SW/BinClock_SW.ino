
#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Time.h>

#include "website.h"
#include "Pins_and_Counters.h"
#include "ASCII_Table.h"

const char* ssid = "BinClock";
const char* password = "";

int sec_cnt = -3;

int Sec_Val = 0;
int Min_Val = 0;
int Hur_Val = 0;

int bright_inc = 2;

int sec_bright = 10;
int min_bright = 10;
int hur_bright = 10;
int max_bright = 40;

bool IP_disp_done = false;

bool disp_user_Flag = false;
int disp_user_cnt = 0;
String message_string = "";
char* test_Arr = new char[128];


ESP32Time rtc(3600);  // set timezone to german gmt+1

IPAddress myIP;

WebServer server(80);

void setup() {
  pinMode(sec_Pin0, OUTPUT);
  pinMode(sec_Pin1, OUTPUT);
  pinMode(sec_Pin2, OUTPUT);
  pinMode(sec_Pin3, OUTPUT);
  pinMode(sec_Pin4, OUTPUT);
  pinMode(sec_Pin5, OUTPUT);

  pinMode(min_Pin0, OUTPUT);
  pinMode(min_Pin1, OUTPUT);
  pinMode(min_Pin2, OUTPUT);
  pinMode(min_Pin3, OUTPUT);
  pinMode(min_Pin4, OUTPUT);
  pinMode(min_Pin5, OUTPUT);

  pinMode(hur_Pin0, OUTPUT);
  pinMode(hur_Pin1, OUTPUT);
  pinMode(hur_Pin2, OUTPUT);
  pinMode(hur_Pin3, OUTPUT);
  pinMode(hur_Pin4, OUTPUT);

  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  myIP = WiFi.softAPIP();

  server.on("/", handleRoot);
  server.begin();
}

void handleRoot() {

  if (server.method() == HTTP_POST) {
    String str_time_set = server.arg("set_T");
    String str_set_dimmer = server.arg("dimmer");
    String str_set_brighter = server.arg("brighter");
    String str_message = server.arg("message_Box");

    if (str_time_set.length() > 0) {
      Serial.println("Received post to set new time: " + str_time_set);
      char* pEnd;
      long long int time_val = strtoull(str_time_set.c_str(), &pEnd, 10) / 1000;
      rtc.setTime(time_val);
    }
    if (str_set_brighter.length() > 0) {
      Serial.println("set brightness higher");
      sec_bright += bright_inc;
      min_bright += bright_inc;
      hur_bright += bright_inc;
      if (sec_bright > max_bright) { sec_bright = max_bright; };
      if (min_bright > max_bright) { min_bright = max_bright; };
      if (hur_bright > max_bright) { hur_bright = max_bright; };
    }
    if (str_set_dimmer.length() > 0) {
      Serial.println("set the brightness lower");
      sec_bright -= bright_inc;
      min_bright -= bright_inc;
      hur_bright -= bright_inc;
      if (sec_bright < 1) { sec_bright = 1; };
      if (min_bright < 1) { min_bright = 1; };
      if (hur_bright < 1) { hur_bright = 1; };

      Serial.println(sec_bright);
    }
    if (str_message.length() > 0) {
      message_string = str_message;
      disp_user_Flag = true;
      disp_user_cnt = 0;
      strcpy(test_Arr, message_string.c_str());
    }

    server.send(200, "text/html", websiteHTML);

  } else {
    server.send(200, "text/html", websiteHTML);
  }
}

void loop() {

  server.handleClient();
  if (!IP_disp_done) {
    if (sec_cnt <= 0) {
      Sec_Val = 63;
      Min_Val = 63;
      Hur_Val = 31;
    }

    sec_cnt++;

    if (sec_cnt == 1) {
      Sec_Val = ASCII_table['I'-32][2];
      Min_Val = ASCII_table['I'-32][1];
      Hur_Val = ASCII_table['I'-32][0];
    }

    if (sec_cnt == 2) {
      Sec_Val = ASCII_table['P'-32][2];
      Min_Val = ASCII_table['P'-32][1];
      Hur_Val = ASCII_table['P'-32][0];
    }

    if (sec_cnt == 3) {
      Sec_Val = ASCII_table[':'-32][2];
      Min_Val = ASCII_table[':'-32][1];
      Hur_Val = ASCII_table[':'-32][0];
    }

    if ((sec_cnt > 3) & (sec_cnt < 16)) {
      char* temp_Arr = new char[35];
      strcpy(temp_Arr, myIP.toString(0).c_str());
        Sec_Val = ASCII_table[(temp_Arr[sec_cnt - 4]) - 32][2];
        Min_Val = ASCII_table[(temp_Arr[sec_cnt - 4]) - 32][1];
        Hur_Val = ASCII_table[(temp_Arr[sec_cnt - 4]) - 32][0];
    }
    if (sec_cnt == 16) {
      Sec_Val = 63;
      Min_Val = 63;
      Hur_Val = 31;
      IP_disp_done = true;
      sec_cnt = 0;
    }
  } else if (disp_user_Flag) {
    Sec_Val = ASCII_table[(int)test_Arr[disp_user_cnt] - 32][2];
    Min_Val = ASCII_table[(int)test_Arr[disp_user_cnt] - 32][1];
    Hur_Val = ASCII_table[(int)test_Arr[disp_user_cnt] - 32][0];
    disp_user_cnt++;
  } else {
    Sec_Val = rtc.getSecond();
    Min_Val = rtc.getMinute();
    Hur_Val = rtc.getHour(true);
  }

  sec_Val0 = (Sec_Val >> 0) & (0x1);
  sec_Val1 = (Sec_Val >> 1) & (0x1);
  sec_Val2 = (Sec_Val >> 2) & (0x1);
  sec_Val3 = (Sec_Val >> 3) & (0x1);
  sec_Val4 = (Sec_Val >> 4) & (0x1);
  sec_Val5 = (Sec_Val >> 5) & (0x1);

  min_Val0 = (Min_Val >> 0) & (0x1);
  min_Val1 = (Min_Val >> 1) & (0x1);
  min_Val2 = (Min_Val >> 2) & (0x1);
  min_Val3 = (Min_Val >> 3) & (0x1);
  min_Val4 = (Min_Val >> 4) & (0x1);
  min_Val5 = (Min_Val >> 5) & (0x1);

  hur_Val0 = (Hur_Val >> 0) & (0x1);
  hur_Val1 = (Hur_Val >> 1) & (0x1);
  hur_Val2 = (Hur_Val >> 2) & (0x1);
  hur_Val3 = (Hur_Val >> 3) & (0x1);
  hur_Val4 = (Hur_Val >> 4) & (0x1);

  if (!IP_disp_done | disp_user_Flag) {
    analogWrite(sec_Pin0, 0);  // 15
    analogWrite(sec_Pin1, 0);
    analogWrite(sec_Pin2, 0);
    analogWrite(sec_Pin3, 0);
    analogWrite(sec_Pin4, 0);
    analogWrite(sec_Pin5, 0);
    analogWrite(min_Pin0, 0);  // 25
    analogWrite(min_Pin1, 0);
    analogWrite(min_Pin2, 0);
    analogWrite(min_Pin3, 0);
    analogWrite(min_Pin4, 0);
    analogWrite(min_Pin5, 0);
    analogWrite(hur_Pin0, 0);  // 10
    analogWrite(hur_Pin1, 0);
    analogWrite(hur_Pin2, 0);
    analogWrite(hur_Pin3, 0);
    digitalWrite(hur_Pin4, 0);
    delay(300);
  }
  // this needs to be placed here because otherwise, the last element of the message is displayed for a too short period of time.
  if (disp_user_cnt > message_string.length() - 1) {
    disp_user_Flag = false;
    message_string = "";
  }
  analogWrite(sec_Pin0, sec_Val0 * sec_bright);  // 15
  analogWrite(sec_Pin1, sec_Val1 * sec_bright);
  analogWrite(sec_Pin2, sec_Val2 * sec_bright);
  analogWrite(sec_Pin3, sec_Val3 * sec_bright);
  analogWrite(sec_Pin4, sec_Val4 * sec_bright);
  analogWrite(sec_Pin5, sec_Val5 * sec_bright);
  analogWrite(min_Pin0, min_Val0 * min_bright);  // 25
  analogWrite(min_Pin1, min_Val1 * min_bright);
  analogWrite(min_Pin2, min_Val2 * min_bright);
  analogWrite(min_Pin3, min_Val3 * min_bright);
  analogWrite(min_Pin4, min_Val4 * min_bright);
  analogWrite(min_Pin5, min_Val5 * min_bright);
  analogWrite(hur_Pin0, hur_Val0 * hur_bright);  // 10
  analogWrite(hur_Pin1, hur_Val1 * hur_bright);
  analogWrite(hur_Pin2, hur_Val2 * hur_bright);
  analogWrite(hur_Pin3, hur_Val3 * hur_bright);
  digitalWrite(hur_Pin4, hur_Val4);

  if (!IP_disp_done) {
    delay(1000);
  } else {
    delay(500);
  }
}