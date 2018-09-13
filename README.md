# ESP8266 MQTT Blind Controller
A set of arduino sketches to use on an ESP8266 board so you can open and close your blinds by publishing to an MQTT Topic. The initial version also features temperature recording. The initial realease is only designed for vertical blinds which require very little tourque.

The first release is up now. The basica installation is:

1. Install [PlatformIO](https://platformio.org/)
2. Installed the libararies required by either cloning their source or using PlatformIOs library manager:
* AccelStepper
* OneWire
* PubSubClient
* DallasTemperature
3. Build and upload the project using PlatformIO's project tasks then "Upload File System Image" from the same task menu.

The Hardware required is:
* Wemos D1 Mini
* 28BYJ-48 stepper motor and ULN2003 driver (for vertical blinds)
* Dupont jumpers
* 3D Printed cog, or a cog taken from replacement blind parts
* Hot Glue
