# ESP8266 MQTT Blind Controller
## This might require some tweaking and isn't a production ready project.
A set of arduino sketches to use on an ESP8266 board so you can open and close your blinds by publishing to an MQTT Topic. The initial version also features temperature recording. I have changed this project to now use a normal motor with a rotary encoder rather than the underpowered stepper motor I was previously using.

The first release is up now. The basic installation is:

1. Install [PlatformIO](https://platformio.org/)
2. Installed the libararies required by either cloning their source or using PlatformIOs library manager:
* AccelStepper
* OneWire
* PubSubClient
* DallasTemperature
3. Build and upload the project using PlatformIO's project tasks then "Upload File System Image" from the same task menu.

The Hardware required is:
* Wemos D1 Mini
* ZGY370EC DC motor with hall encoder 11PPR JGY370
* L298N Motor driver
* Dupont jumpers
* 12v to 5v DC-DC converter
* 12v power supply
* 3D Printed cog, or a cog taken from replacement blind parts
* Hot Glue
