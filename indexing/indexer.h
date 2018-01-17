
#include "common/index.pb.h"

#include <string>
#include <vector>

namespace indexing {

// Builds index that can be used to do prefix matching of words in variable names.
// See common/index.proto for indexing information.
// expects input in format in separate strings:
// <variable_name_1_string> <score_1_int>
// <variable_name_2_string> <score_2_int>
// ...
// This function does not validate input, please make sure input is in specified format.
common::Index BuildIndex(const std::vector<std::string>& line);

}  // namespace indexing

