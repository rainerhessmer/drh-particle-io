#include "utils.h"

int Utils::parseTimePeriod(String input, int &seconds) {
    int start_index = 0;
    int part_count = 0; // We expect at most three parts for hh, mm, and ss
    seconds = 0;
    while (start_index >= 0) {
        if (part_count == 3) {
            //Serial.println("Too many entries");
            seconds = 0;
            return -1;
        }
        String part = getNextValue(input, ':', start_index);
        //Serial.println("part: " + part);
        int value = atoi(part.c_str()); // TODO: Catch conversion error

        seconds = seconds * 60 + value;
        part_count++;
    }
    return 0;
}

String Utils::getNextValue(const String input, const char delimiter, int &start_index) {
    String result;
    int delimiter_index = input.indexOf(delimiter, start_index);
    //Serial.println("comma index: " + String(delimiter_index));
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
