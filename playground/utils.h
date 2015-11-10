#include "application.h"
#include "logger.h"
#include <vector>

#ifndef utils_h
#define utils_h

class Utils {
 public:
  // Parses a text in the form hh:mm:ss and returns the corresponding
  // number of seconds in the seconds parameters. The hh and mm parts
  // are optional; i.e., input in the form mm:ss and ss is accepted
  // as well.
  //
  // Returns 0 if sucssessful; -1 otherwise.
  static int parseTimePeriod(String input, int &seconds);
  
  static String getNextValue(const String input, const char delimiter, int &start_index);
  
  // Parsing durations definition in the form
  // durations:'1:12','1:22:33','','5'
  static int parseDurations(String input, std::vector<int> &durations);
 private:
  static Logger logger_;
};

#endif // utils_h