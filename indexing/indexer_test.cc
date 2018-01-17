#include "indexing/indexer.h"

#include "googletest/include/gtest/gtest.h"
#include "common/index.pb.h"

namespace indexing {

using std::map;
using std::string;
using std::vector;

TEST(IndexerTest, BuildIndexTest) {
  const auto index = BuildIndex({"a_temporary_variable 5", "this_is_a_long_variable_name 1", "this_variable_is_obsolete 2"});
  ASSERT_EQ(3, index.variable_size());
  EXPECT_EQ("a_temporary_variable", index.variable(0).name());
  EXPECT_EQ(5, index.variable(0).score());
  EXPECT_EQ("this_variable_is_obsolete", index.variable(1).name());
  EXPECT_EQ(2, index.variable(1).score());
  EXPECT_EQ("this_is_a_long_variable_name", index.variable(2).name());
  EXPECT_EQ(1, index.variable(2).score());
  map<string, vector<int>> expected{
    {"a", {0, 2}},
    {"is", {1, 2}},
    {"long", {2}},
    {"name", {2}},
    {"obsolete", {1}},
    {"temporary", {0}},
    {"this", {1, 2}},
    {"variable", {0, 1, 2}}
  };
  ASSERT_EQ(expected.size(), index.word_size());
  for (const auto& metadata : index.word()) {
    ASSERT_TRUE(expected.find(metadata.word()) != expected.end());
    const auto& indices = expected[metadata.word()];
    ASSERT_EQ(indices.size(), metadata.variable_index_size());
    for (uint i = 0; i < indices.size(); i++) {
      EXPECT_EQ(indices[i], metadata.variable_index(i));
    }
  }
}

}  // namespace indexing
