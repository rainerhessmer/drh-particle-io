#include "utils.h"
#include "logger.h"

int Utils::parseTimePeriod(String input, int &seconds) {
    int start_index = 0;
    int part_count = 0; // We expect at most three parts for hh, mm, and ss
    seconds = 0;
    while (start_index >= 0) {
        if (part_count == 3) {
            logger_.logError("parseTimePeriod - too many parts in '" + input +"'");
            return -1;
        }
        String part = getNextValue(input, ':', start_index);
        //logger_.logDebug("- part: " + part);
        int value = atoi(part.c_str());
        //logger_.logDebug("- value: " + String(value));
        
        seconds = seconds * 60 + value;
        part_count++;
    }
    return 0;
}

String Utils::getNextValue(const String input, const char delimiter, int &start_index) {
    String result;
    int delimiter_index = input.indexOf(delimiter, start_index);
    if (delimiter_index == -1) {
        // no more commas
        result = input.substring(start_index);
        start_index = -1;
    } else {
        result = input.substring(start_index, delimiter_index);
        start_index = delimiter_index + 1;
    }
    return result;
}

int Utils::parseDurations(String input, std::vector<int> &durations) {
    String expected_prefix = "durations:";
    String actual_prefix = input.substring(0, expected_prefix.length());
    logger_.logDebug("actual_prefix: " + actual_prefix);
    if (actual_prefix != expected_prefix) {
        // Wrong prefix
        return -1;
    }
    
    String comma_separated_durations = input.substring(expected_prefix.length());
    int start_index = 0;
    while (start_index >= 0) {
        String part = getNextValue(comma_separated_durations, ',', start_index);
        logger_.logDebug("raw duration part: " + part);
        // Part must be bookended by '
        if (part.charAt(0) != '\'' || part.charAt(part.length() - 1) != '\'') {
            logger_.logError("duration not wrapped in '");
            return -1;
        }
        String durationString = part.substring(1, part.length() - 1);
        logger_.logDebug("duration part: " + durationString);
        int duration = 0;
        int result_code = parseTimePeriod(durationString, duration);
        if (result_code < 0) {
            logger_.logError("parse error");
            return result_code;
        } else {
            logger_.logDebug("parsed duration: " + String(duration));
            durations.push_back(duration);
        }
    }
    return 0;
}

Logger Utils::logger_ = Logger("Utils");
