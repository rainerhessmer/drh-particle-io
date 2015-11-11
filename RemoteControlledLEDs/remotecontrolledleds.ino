#include "utils.h"

#include <vector>

std::vector<int> leds = {D0, D1, D2, D3};
int led_index = 0;
String capabilities = String::format("{ \"channels\": %d }", leds.size());

void setup() {
    for (auto led : leds) {
        pinMode(led, OUTPUT);
    }
    Particle.function("leds", handleLEDsCommand);
    Particle.variable("capabilities", capabilities);
    Serial.begin(9600);
}

void loop() {
}

void logToSerial(String message) {
    Serial.println(message);
}

int handleLEDsCommand(String command) {
    /* Spark.functions always take a string as an argument and return an integer.
    Expected input: <0|1>,<0|1>,<0|1>,<0|1> indicating the desired state of the LEDs.
    Example: "1,0,0,1" turns on the first and last LED.

    Returns 1 if the command could be parsed and applied; otherwise -1.
    */

    Serial.println("Handling command " + command);
    int led_index = 0;
    int start_index = 0;
    while (start_index >= 0) {
        Serial.println("LED index: " + String(led_index));
        if (led_index == leds.size()) {
            Serial.println("Too many entries");
            return -1;
        }
        String value = Utils::getNextValue(command, ',', start_index);
        Serial.println("value: " + value);
        int led = leds.at(led_index);
        if (value == "0") {
            Serial.println("writing LOW");
            digitalWrite(led, LOW);
        } else if (value == "1") {
            Serial.println("writing HIGH");
            digitalWrite(led, HIGH);
        } else {
            Serial.println("Unexpected value at index " + String(led_index));
            return -1;
        }

        led_index++;
    }

    Serial.println("Done with command " + command);
    Serial.println();
    return 0;
}
