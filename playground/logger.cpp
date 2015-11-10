#include "logger.h"

void Logger::setMinLevel(Level min_level) {
    min_level_ = min_level;
}
void Logger::logToSerial() {
    log_writer_ = Logger::serialWriter;
}
String Logger::levelAsString(Level level) {
    switch(level) {
        case Level::DEBUG: return "DEBUG";
        case Level::INFO: return "INFO";
        case Level::WARN: return "WARN";
        case Level::ERROR: return "ERROR";
    }
    return "????";
}
void Logger::serialWriter(const String message) {
    Serial.println(message);
}
void Logger::noopWriter(const String message) {
}

Logger::Level Logger::min_level_ = Logger::Level::ERROR;
Logger::LogWriterFunction Logger::log_writer_ = Logger::noopWriter;

Logger::Logger(String logger_name) : logger_name_(logger_name) {
}
void Logger::logDebug(const String message) {
    log(Level::DEBUG, message);
}
void Logger::logInfo(const String message) {
    log(Level::INFO, message);
}
void Logger::logWarn(const String message) {
    log(Level::WARN, message);
}
void Logger::logError(const String message) {
    log(Level::ERROR, message);
}
void Logger::log(Level level, const String message) {
    if (level >= min_level_) {
        log_writer_(logger_name_ + "[" + levelAsString(level) + "] - " + message);
    }
}
