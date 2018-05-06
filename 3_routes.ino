//Todo create functions to handle all of the below calls
/*
 * URL: speed ->  Params: amount 0-100  X
 * URL: limit -> Params: amount 0 or 100  X
 * URL: turn -> Params: amount -0.5 - +0.5 X
 * URL: mqtt -> Params: clientID server username password
 * URL: reset
 */

/*
 * The root route, has all the base html and the javascript to interact with the other routes
 */
void handleRoot() {
    //Todo: add in the javascript element to this code.
    String returnHtml = "<h2>Blind Config</h2>"
                        "<!--https://purecss.io/forms/-->"
                        "<div class='pure-form pure-form-stacked'>"
                        "<fieldset>"
                        "<h3>MQTT</h3>"
                        "<label for='clientID'>Client ID</label>"
                        "<input type='text' id='clientID' /><br />"
                        "Server: <input type='text' id='server' /><br />"
                        "Username: <input type='text' id='username' /><br />"
                        "Password: <input type='text' id='password' /><br />"
                        "<input type='button' id='setMqtt' value='Save MQTT' class='pure-button pure-button-primary' onclick='saveMQTT();' />"
                        "</fieldset>"
                        ""
                        "<h3>Range Set</h3>"
                        "<h4>CW</h4>"
                        "<fieldset>"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(0.5);' value='1/2 Turn' />"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(0.1250);' value='1/8 Turn' />"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(0.0625);' value='1/16 Turn' />"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(0.015625);'value='1/64 Turn' />"
                        "</fieldset>"
                        "<h4>CCW</h4>"
                        "<fieldset>"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.5);' value='1/2 Turn' />"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.1250);' value='1/8 Turn' />"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.0625);' value='1/16 Turn' />"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.015625);' value='1/64 Turn' />"
                        "</fieldset>"
                        "<br /><br />"
                        "<button class='pure-button pure-button-primary' onclick='limit(0);'>Set 0%</button>"
                        "<button class='pure-button pure-button-primary' onclick='limit(100);'>Set 100%</button>"
                        "<br /><br />"
                        "<button class='pure-button pure-button-primary' onclick='goto(0);'>Go To 0%</button>"
                        "<button class='pure-button pure-button-primary' onclick='goto(100);'>Go To 100%</button>"
                        ""
                        "<h4>Speed Set</h4>"
                        "<input type='number' id='rangeNumber' min='1' max='100' value='100'  onchange='setSpeed(this.value);'/>"
                        "<input type='range' id='speedRange' style='width:90%;' min='1' max='100' value='100'  onchange='setSpeed(this.value);'/>"
                        "</div>"
                        "<script type='text/javascript'>"
                        "function makeRequest(url, params) {"
                        "alert('Startin Request');"
                        "url = '/' + url;"
                         "var http = new XMLHttpRequest();"
                         "var encodedParams = '';"
                         "for (var key in params) {"
                         "encodedParams += key+'='+ params[key]+'&';"
                         "};"
                         "alert('Posting to: ' + url + ' with params: ' +encodedParams );"
                         "encodedParams = encodedParams.slice(0, -1);"
                         "http.open('POST', url, true);"
                         "http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');"
                         "http.onreadystatechange = function() {/*Call a function when the state changes.*/"
                         "if(http.readyState == 4 && http.status == 200) {"
                         "alert(http.responseText);"
                         "};"
                         "};"
                         "http.send(encodedParams);"
                         "alert(http.responseText);"
                         "};"
                         ""
                         "function saveMQTT() {"
                         "var params = {"
                         "'clientID' : document.getElementById('clientID').value,"
                         "'server' : document.getElementById('server').value,"
                         "'username': document.getElementById('username').value,"
                         "'password': document.getElementById('password').value,"
                         "};"
                         "makeRequest('mqtt', params);"
                         "};"
                         ""
                         "function turn(amount) {"
                         "makeRequest('turn', {'amount' : amount});"
                         "};"
                         ""
                         "function limit(amount) {"
                         "makeRequest('limit', {'amount' : amount});"
                         "};"
                         ""
                         "function setSpeed(amount) {"
                         "document.getElementById('rangeNumber').value=amount;"
                         "document.getElementById('speedRange').value=amount;"
                         "makeRequest('speed', {'amount' : amount});"
                         "};"
                        "function goto(place) {"
                                "makeRequest('goto', {'place' : place});"
                        "};"
                         "</script>";

    /*
         "<h2>Blind Config</h2>"
    "<!--https://purecss.io/forms/-->"
    "<div class='pure-form pure-form-stacked'>"
        "<fieldset>"
            "<h3>MQTT</h3>"
            "<label for='clientID'>Client ID</label>"
            "<input type='text' id='clientID' /><br />"
            "Server: <input type='text' id='server' /><br />"
            "Username: <input type='text' id='username' /><br />"
            "Password: <input type='text' id='password' /><br />"
            "<input type='button' id='setMqtt' value='Save MQTT' class='pure-button pure-button-primary' onclick='saveMQTT();' />"
        "</fieldset>"
    ""
        "<h3>Range Set</h3>"
        "<h4>CW</h4>"
        "<fieldset>"
            "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.5);' value='1/2 Turn' />"
            "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.1250);' value='1/8 Turn' />"
            "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.0625);' value='1/16 Turn' />"
            "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.015625);'value='1/64 Turn' />"
        "</fieldset>"
        "<h4>CCW</h4>"
        "<fieldset>"
            "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.5);' value='1/2 Turn' />"
            "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.1250);' value='1/8 Turn' />"
            "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.0625);' value='1/16 Turn' />"
            "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.015625);' value='1/64 Turn' />"
        "</fieldset>"
        "<br /><br />"
        "<button class='pure-button pure-button-primary' onclick='limit(0);'>Set 0%</button>"
        "<button class='pure-button pure-button-primary' onclick='limit(100);'>Set 100%</button>"
    ""
        "<h4>Speed Set</h4>"
        "<input type='number' id='rangeNumber' min='1' max='100' value='100'  onchange='setSpeed(this.value);'/>"
        "<input type='range' id='speedRange' style='width:90%;' min='1' max='100' value='100'  onchange='setSpeed(this.value);'/>"
    "</div>"
    "<script type='text/javascript'>"
        "function makeRequest(url, params) {"
            "alert('Startin Request');"
            "url = "/" + url;"
            "var http = new XMLHttpRequest();"
            "var encodedParams = '';"
            "for (var key in params) {"
                "encodedParams += key+'='+ params[key]+'&';"
            "}"
            "alert('Posting to: ' + url + ' with params: ' +encodedParams );"
            "encodedParams = encodedParams.slice(0, -1)"
            "http.open('POST', url, true);"
            "http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');"
            "http.onreadystatechange = function() {//Call a function when the state changes."
                "if(http.readyState == 4 && http.status == 200) {"
                    "alert(http.responseText);"
                "}"
            "}"
            "http.send(encodedParams);"
            "alert(http.responseText);"
        "}"
    ""
        "function saveMQTT() {"
            "var params = {"
                "'clientID' : document.getElementById('clientID').value,"
                "'server' : document.getElementById('server').value,"
                "'username': document.getElementById('username').value,"
                "'password': document.getElementById('password').value,"
            "};"
            "makeRequest('mqtt', params);"
        "}"
    ""
        "function turn(amount) {"
            "makeRequest('turn', {'amount' : amount});"
        "}"
    ""
        "function limit(amount) {"
            "makeRequest('limit', {'amount' : amount});"
        "}"
    ""
        "function setSpeed(amount) {"
            "document.getElementById('rangeNumber').value=amount;"
            "document.getElementById('speedRange').value=amount;"
            "makeRequest('speed', {'amount' : amount});"
        "}"
    "</script>"
     */

    server.send(200, "text/html", returnHtml);

}

void speedChange() {
    //Todo: add to save feature.
    for (uint8_t i=0; i<server.args(); i++) {
        if (server.argName(i) == "amount") {
            int amount = server.arg(i).toInt();
            saveSetting("speed", String(amount));
            break;
        }
    }
    server.send(200, "text/html", "ok");
}

void limitSet() {
    //Todo: add to save feature.
    for (uint8_t i=0; i<server.args(); i++) {
        if (server.argName(i) == "amount") {
            int amount = server.arg(i).toInt();
            if (amount == 0) {
                saveSetting("lowerLimit", String(stepper.currentPosition()));
            } else if(amount == 100) {
                saveSetting("upperLimit", String(stepper.currentPosition()));
            }
            break;
        }
    }
    server.send(200, "text/html", "ok");
}

void manualTurn() {
    //Todo: add to save feature.
    for (uint8_t i=0; i<server.args(); i++) {
        if (server.argName(i) == "amount") {
            float amount = server.arg(i).toFloat();
            stepByTurnAmount(amount);
            break;
        }
    }
    server.send(200, "text/html", "ok");
}

void mqttSettings() {
    //Todo: add to save feature.
    for (uint8_t i=0; i<server.args(); i++) {
        if (server.argName(i) == "clientID") {
            saveSetting("clientId", server.arg(i));
        } else if (server.argName(i) == "server") {
            saveSetting("server", server.arg(i));
        } else if (server.argName(i) == "username") {
            saveSetting("username", server.arg(i));
        } else if (server.argName(i) == "password") {
            saveSetting("password", server.arg(i));
        }
    }
    server.send(200, "text/html", "ok");
}

void setWifiDetails() {
    //Todo: add to save feature.
    for (uint8_t i=0; i<server.args(); i++) {
        if (server.argName(i) == "ssid") {
            saveSetting("ssid", server.arg(i));
        } else if (server.argName(i) == "password") {
            saveSetting("pass", server.arg(i));
        }
    }
    server.send(200, "text/html", "ok");
}

void goTo() {
    //Todo: add to save feature.
    for (uint8_t i=0; i<server.args(); i++) {
        if (server.argName(i) == "place") {
            if (server.arg(i) == "100") {
                stepToHundred();
            } else {
                stepToZero();
            }
            break;
        }
    }
    server.send(200, "text/html", "ok");
}

void softReset() {
    server.send(200, "text/html", "ok");
    ESP.restart();
}

void setupRoutes(){
    server.begin();
    //Todo: add more routes
    server.on("/", handleRoot);
    server.on("/speed", speedChange);
    server.on("/limit", limitSet);
    server.on("/turn", manualTurn);
    server.on("/mqtt", mqttSettings);
    server.on("/wifi", setWifiDetails);
    server.on("/goto", goTo);
    server.on("/reset", softReset);
}

