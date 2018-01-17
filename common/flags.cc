#include "common/flags.h"

#include <iostream>

namespace common {

using std::string;

string GetFlagOrDie(const string& flag_name, const string& flag_value) {
  if (flag_value == "") {
    std::cout << "ERROR: " << flag_name << " flag is required, Empty value provided." << std::endl;
    exit(1);
  }
  return flag_value;
}

}  // namespace common
