
#include "common/index.pb.h"

namespace common {

// Reads file at index_path and deserializes it into Index proto and returns it.
// Stops program if deserialization fails.
Index ReadIndexOrDie(const std::string& index_path);

}  // namespace common
