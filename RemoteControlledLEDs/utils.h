#include "application.h"

#ifndef utils_h
#define utils_h

class Utils {
 public:
  typedef std::function<void (const String message)> LogFunction;

  // Parses a text in the form hh:mm:ss and returns the corresponding
  // number of seconds in the seconds parameters. The hh and mm parts
  // are optional; i.e., input in the form mm:ss and ss is accepted
  // as well.
  //
  // Returns 0 if sucssessful; -1 otherwise.
  static int parseTimePeriod(String input, int &seconds);

  static String getNextValue(const String input, const char delimiter, int &start_index);
};

#endif // utils_h
