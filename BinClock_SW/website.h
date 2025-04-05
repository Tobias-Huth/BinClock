#ifndef WEBSITE_H
#define WEBSITE_H
#include <pgmspace.h>



const char* websiteHTML PROGMEM = R"rawliteral(
<!doctype html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Binary Clock set time</title>
<style>
    body{
        background-color: black;
    }
    h1 {
    text-decoration: none;
    color: #4583c2;
    size: 20px;
    }
    p {
    margin-top: 15px;
    margin-bottom: 0px;
    padding: 0px;
    font-size: 16px;
    color: wheat;
    }
    button {
    font-weight: bold;
    font-size: 16px;
    border-color: aqua;
    background-color: rgb(20, 173, 220);
    padding-block: 5px;
    border-radius: 5px;
    margin: 10px;
    }
    label{
        margin:5px;
        color: white;
    }
    input{
        background-color: black;
        color: wheat;
    }
    output{
        background-color: black;
        color: wheat;
    }
    </style>
</head>
<body>
    <form>
        <h1>Superstarke Bin&aumlruhr</h1>
        <p>aktuelle Uhrzeit und Datum:</p>
        <input name="act_hur" id="act_hur" value="00" size="1"/> <label>:</label>
        <input name="act_min" id="act_min" value="00" size="1"/><label>:</label>
        <input name="act_sec" id="act_sec" value="00" size="1"/><br>
        <input name="act_day" id="act_day" value="00" size="1"/> <label>.</label>
        <input name="act_mon" id="act_mon" value="00" size="1"/><label>.</label>
        <input name="act_yer" id="act_yer" value="00" size="1"/><br>
    </form>
    <form  method="POST">
        <p>Uhrzeit setzen der nerdigen Uhr:</p>
        <input name = "set_T" id="set_T" value="0"/>
        <button id="set_time" name="btn" value="timeset">Setzen</button>
    </form>
    <form method="POST">
        <button name="brighter" id="brighter" value="0">heller</button>
        <button name="dimmer" id="dimmer" value="0">dunkler</button>
    </form>
    <form method="POST">
        <p>Nachricht anzeigen:</p>
        <input name="message_Box" id="message_Box" value="Hallo!"/>
        <button name="send_message" id="send_message" value="0">Senden</button>
    </form>
    <hr>
    <p>Dieses Hammergeschenk f&uumlr <font-size: 16px;>DICH</font-size:> gab es zum Studikumpeltreffen <b><font-size: 16px;>2024</font-size:></b> im herrlichen <b><font-size: 16px;>Bremen</font-size:></b></p>

    <script>
    // Get current date and time
    Date.prototype.stdTimezoneOffset = function () {
    var jan = new Date(this.getFullYear(), 0, 1);
    var jul = new Date(this.getFullYear(), 6, 1);
    return Math.max(jan.getTimezoneOffset(), jul.getTimezoneOffset());
    }

    Date.prototype.isDstObserved = function () {
        return this.getTimezoneOffset() < this.stdTimezoneOffset();
    }

    function update_time(){
        var now = new Date();
        var seconds = now.getSeconds()
        var minutes = now.getMinutes()
        var hours   = now.getHours()
        var day     = now.getDay()
        var month   = now.getMonth()
        var year   = now.getFullYear()

        var since_epoch = now.getTime()
        if (now.isDstObserved()) { 
          since_epoch += 3600000
        }
        document.getElementById("act_sec").value = seconds;
        document.getElementById("act_min").value = minutes;
        document.getElementById("act_hur").value = hours;
        document.getElementById("act_day").value = day;
        document.getElementById("act_mon").value = month;
        document.getElementById("act_yer").value = year;
        
        document.getElementById("set_T").value = since_epoch;
        
        }
        intervallID = setInterval(update_time,500);
    </script>
</body>
</html>
)rawliteral";

#endif
