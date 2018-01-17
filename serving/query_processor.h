
#include <vector>
#include <string>
#include <map>

#include "common/index.pb.h"

namespace serving {

// Loads index in memory and helps searching query.
// Thread safe.
class QueryProcessor {
 public:
  QueryProcessor(const common::Index& index);

  // Finds variable names which has some word prefix matching query.
  // Returns maximum n values, if n is greater than max result size index is built for,
  // only max result size based on index is returned.
  // If query is invalid returns empty result, anything that is not matching
  // ^[a-zA-Z0-9$]*$ regex is considered invalid.
  std::vector<std::string> Search(const std::string& query, const uint n = 0) const;

 private:
  std::set<int> SearchForIndices(const std::string& query, const uint n = 0) const;

  const std::vector<std::string> variable_names_;
  const std::map<std::string, std::vector<int>> word_metadata_;
  const uint max_result_size_;
};

}  // namespace serving
