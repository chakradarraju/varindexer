#include <string>

#define FLAGS(x) #x, FLAGS_ ## x

namespace common {

// Returns flag_value if it is not empty, if it is empty quits program.
// Use with FLAGS() macro, to read abc flag GetFlagOrDie(FLAGS(abc)).
std::string GetFlagOrDie(const std::string& flag_name, const std::string& flag_value);

}  // namespace common
