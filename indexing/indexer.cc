#include "indexing/indexer.h"

#include <map>
#include <sstream>
#include <gflags/gflags.h>

#include "absl/strings/str_split.h"

DEFINE_int32(max_result_size, 10, "Number of results to keep per index element.");

namespace indexing {

using std::make_pair;
using std::vector;
using std::pair;
using std::string;
using std::map;
using absl::string_view;

namespace {

vector<pair<int, string>> ParseVariables(const vector<string>& lines) {
  vector<pair<int, string>> result;
  for (const auto& line : lines) {
    string variable_name;
    int score;
    std::istringstream iss(line);
    iss >> variable_name >> score;
    result.push_back(make_pair(score, variable_name));
  }
  return result;
}

}

common::Index BuildIndex(const vector<string>& lines) {
  auto parsed = ParseVariables(lines);
  sort(parsed.begin(), parsed.end());
  reverse(parsed.begin(), parsed.end());
  map<string, vector<int>> metadata;
  for (uint i = 0; i < parsed.size(); i++) {
    const auto& variable = parsed[i].second;
    for (const auto& word : absl::StrSplit(variable, '_')) {
      metadata[string(word)].push_back(i);
    }
  }
  common::Index index;
  for (const auto& score_variable : parsed) {
    auto variable = index.add_variable();
    variable->set_name(score_variable.second);
    variable->set_score(score_variable.first);
  }
  for (const auto& word_metadata : metadata) {
    auto word = index.add_word();
    word->set_word(word_metadata.first);
    for (const int index : word_metadata.second) word->add_variable_index(index);
  }
  index.set_max_result_size(FLAGS_max_result_size);
  return index;
}

}  // namespace indexing
