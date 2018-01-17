#include "serving/query_processor.h"

namespace serving {

using std::vector;
using std::string;
using std::set;
using std::map;

namespace {

string EndQuery(const string query) {
  string result = query;
  result[query.size() - 1]++;
  return result;
}

bool IsValidChar(const char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <='Z') || (c >= '0' && c <= '9') || (c == '$');
}

bool IsValidQuery(const string& query) {
  for (const char c : query) {
    if (!IsValidChar(c)) return false;
  }
  return true;
}

vector<string> BuildVariableNames(const common::Index& index) {
  vector<string> result;
  for (const auto& variable : index.variable()) result.push_back(variable.name());
  return result;
}

map<string, vector<int>> BuildWordMetadata(const common::Index& index) {
  map<string, vector<int>> result;
  for (const auto& metadata : index.word()) {
    for (const int index : metadata.variable_index()) {
      result[metadata.word()].push_back(index);
    }
  }
  return result;
}

}  // namespace

QueryProcessor::QueryProcessor(const common::Index& index) :
    variable_names_(BuildVariableNames(index)),
    word_metadata_(BuildWordMetadata(index)),
    max_result_size_(index.max_result_size()) {}

set<int> QueryProcessor::SearchForIndices(const string& query, const uint n) const {
  string end_query = EndQuery(query);
  auto it = word_metadata_.lower_bound(query);
  const auto end_it = word_metadata_.lower_bound(end_query);
  std::set<int> result;
  for (; it != end_it; it++) {
    for (const int i : it->second) result.insert(i);
    while (result.size() > n) result.erase(std::prev(result.end()));
  }
  return result;
}

vector<string> QueryProcessor::Search(const string& query, const uint n) const {
  if (n == 0 || n > max_result_size_) {
    // If n > max_result_size_ issue a warning the results might be wrong.
    return Search(query, max_result_size_);
  }
  if (!IsValidQuery(query)) {
    // Invalid query, should be logged.
    return {};
  }
  vector<string> result;
  for (const int i : SearchForIndices(query, n)) result.push_back(variable_names_[i]);
  return result;
}

}  // namespace serving
