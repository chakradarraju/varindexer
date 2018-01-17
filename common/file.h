
#include <vector>

#include "common/index.pb.h"

namespace common {

// Writes serialized index proto to index_path file.
void WriteIndexTo(const common::Index& index, const std::string& index_path);

// Reads file and returns a vector<string> with one string per line in file.
std::vector<std::string> GetFileContents(const std::string& text_input);

}  // namespace common
