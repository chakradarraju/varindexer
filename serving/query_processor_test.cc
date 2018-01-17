#include "serving/query_processor.h"

#include <iostream>

#include "indexing/indexer.h"
#include "googletest/include/gtest/gtest.h"

namespace serving {

using std::string;
using std::vector;

TEST(QueryProcessorTest, SearchTest) {
  const auto index = indexing::BuildIndex({"a_temporary_variable 5", "this_is_a_long_variable_name 1", "this_variable_is_obsolete 2"});
  const auto processor = QueryProcessor(index);
  const vector<string> expected({"a_temporary_variable", "this_variable_is_obsolete"});
  EXPECT_EQ(processor.Search("var", 2), expected);
}

TEST(QueryProcessorTest, InvalidQueryTest) {
  const auto index = indexing::BuildIndex({"a_temporary_variable 5", "this_is_a_long_variable_name 1", "this_variable_is_obsolete 2"});
  const auto processor = QueryProcessor(index);
  const vector<string> empty;
  EXPECT_EQ(processor.Search("_var", 2), empty);
}

TEST(QueryProcessorTest, SearchFullWord) {
  const auto index = indexing::BuildIndex({"a_temporary_variable 5", "this_is_a_long_variable_name 1", "this_variable_is_obsolete 2"});
  const auto processor = QueryProcessor(index);
  const vector<string> expected({"this_variable_is_obsolete"});
  EXPECT_EQ(processor.Search("obsolete"), expected);
}

TEST(QueryProcessorTest, PrefixMatchingMultipleWords) {
  const auto index = indexing::BuildIndex({"pqr_abc 1", "pqr_abe_xyz 4", "xyz_abf 2", "abc_123 5", "ac_pqr 7"});
  const auto processor = QueryProcessor(index);
  const vector<string> ab_expected({"abc_123", "pqr_abe_xyz", "xyz_abf", "pqr_abc"});
  EXPECT_EQ(processor.Search("ab"), ab_expected);
  const vector<string> abc_expected({"abc_123", "pqr_abc"});
  EXPECT_EQ(processor.Search("abc"), abc_expected);
  const vector<string> xyz_expected({"pqr_abe_xyz", "xyz_abf"});
  EXPECT_EQ(processor.Search("xyz"), xyz_expected);
}

}  // namespace serving
