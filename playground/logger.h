#include "application.h"
#include <vector>

#ifndef logger_h
#define logger_h

class Logger {
 public:
  enum Level {
    DEBUG=0, INFO=1, WARN=2, ERROR=3
  };
  static void setMinLevel(Level min_level);
  static void logToSerial();
  
  Logger(String logger_name);
  void logDebug(const String message);
  void logInfo(const String message);
  void logWarn(const String message);
  void logError(const String message);

 private:
  typedef std::function<void (const String message)> LogWriterFunction;
  static void noopWriter(const String message);
  static void serialWriter(const String message);
  static String levelAsString(Level level);
  static Level min_level_;
  static LogWriterFunction log_writer_;
  void log(Level level, const String message);
  String logger_name_;
};

#endif // logger_h