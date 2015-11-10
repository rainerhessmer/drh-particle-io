#include "logger.h"
#include "utils.h"
#include <vector>

std::vector<int> durations;
Logger logger_("Main");

void setup() {
    Serial.begin(9600);
    Logger::setMinLevel(Logger::Level::DEBUG);
    Logger::logToSerial();
}

void testTimePeriodParsing(String text) {
    int value = 0;
    int result = Utils::parseTimePeriod(text, value);
    logger_.logDebug(text + ": " + String(value) + ": " + String(result));
}

// Tests the passing of string in this form:
// durations:'1:12','1:22:33','','5'
void testDurationsParsing(String text) {
    std::vector<int> durations = {};
    int result_code = Utils::parseDurations(text, durations);
    logger_.logDebug(text + ": " + String(result_code));
    for (auto duration : durations) {
        logger_.logDebug(String(duration));
    }
}

void loop() {
    testTimePeriodParsing("");
    testTimePeriodParsing("12");
    //testTimePeriodParsing("01:02");
    //testTimePeriodParsing("01:02:03");
    //testTimePeriodParsing("01:02:03:03");
    
    logger_.logInfo("---Durations--------------------");
    testDurationsParsing("durations:'1:12','1:22:33','','5'");
    logger_.logInfo("--------------------------------");

    delay(10000);
}