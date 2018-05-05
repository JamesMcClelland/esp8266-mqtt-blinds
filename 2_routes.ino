//Todo create functions to handle all of the below calls
/*
 * URL: speed ->  Params: amount 0-100  X
 * URL: limit -> Params: amount 0 or 100  X
 * URL: turn -> Params: amount -0.5 - +0.5
 * URL: mqtt -> Params: clientID server username password
 */

/*
 * The root route, has all the base html and the javascript to interact with the other routes
 */
void handleRoot() {
    //Todo: add in the javascript element to this code.
    String returnHtml = "<h2>Blind Config</h2>"
                        "<!--https://purecss.io/forms/-->"
                        "<form class='pure-form pure-form-stacked'>"
                        "<fieldset>"
                        "<h3>MQTT</h3>"
                        "<label for='clientID'>Client ID</label>"
                        "<input type='text' id='clientID' /><br />"
                        "Server: <input type='text' id='server' /><br />"
                        "Username: <input type='text' id='username' /><br />"
                        "Password: <input type='text' id='password' /><br />"
                        "      <input type='button' id='setMqtt' value='Save MQTT' class='pure-button pure-button-primary' onclick='saveMQTT();' />"
                        "</fieldset>"

                        "<h3>Range Set</h3>"
                        "<h4>CW</h4>"
                        "<fieldset>"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.5);' value='1/2 Turn' />"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.1250);' value='1/8 Turn' />"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.0625);' value='1/16 Turn' />"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.015625);'value='1/64 Turn' />"
                        "      </fieldset>"
                        "<h4>CCW</h4>"
                        "      <fieldset>"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.5);' value='1/2 Turn' />"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.1250);' value='1/8 Turn' />"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.0625);' value='1/16 Turn' />"
                        "<input type='button' class='pure-button pure-button-primary' onclick='turn(-0.015625);' value='1/64 Turn' />"
                        "      </fieldset>"
                        "<br /><br />"
                        "<button class='pure-button pure-button-primary' onclick='limit(0);'>Set 0%</button>"
                        "<button class='pure-button pure-button-primary' onclick='limit(100);'>Set 100%</button>"

                        "<h4>Speed Set</h4>"
                        "<input type='number' id='rangeNumber' min='1' max='100' value='100'  onchange='setSpeed(this.value);'/>"
                        "<input type='range' id='speedRange' style='width:90%;' min='1' max='100' value='100'  onchange='setSpeed(this.value);'/>"
                        "</form>";


    server.send(200, "text/html", returnHtml);

}

void speedChange() {
    //Todo: add to save feature.
    for (uint8_t i=0; i<server.args(); i++) {
        if (server.argName(i) == "amount") {
            int amount = server.arg(i).toInt();
            saveSetting("speed", amount, "");
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
                saveSetting("lowerLimit", amount, "");
            } else if(amount == 100) {
                saveSetting("upperLimit", amount, "");
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
            int amount = server.arg(i).toInt();
            if (amount == 0) {
                saveSetting("lowerLimit", amount, "");
            } else if(amount == 100) {
                saveSetting("upperLimit", amount, "");
            }
            break;
        }
    }
    server.send(200, "text/html", "ok");
}

void setupRoutes(){
    server.begin();
    //Todo: add more routes
    server.on("/", handleRoot);
    server.on("/speed", speedChange);
    server.on("/limit", limitSet);
}

