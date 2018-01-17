// Builds index from passed text_input file and writes it to index_path file.
// Both text_input and index_path flags are required.
// See indexing/indexer.h for input format.
//
// Usage:
// bazel build indexing:build_index -c opt && \
// time bazel-bin/indexing/build_index --text_input=$BASE/data/vars \
// --index_path=$BASE/data/index

#include <gflags/gflags.h>

#include "common/file.h"
#include "common/flags.h"
#include "indexing/indexer.h"

DEFINE_string(text_input, "", "Path to read text input from. Required.");
DEFINE_string(index_path, "", "Path to write index to. Required.");

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  WriteIndexTo(
      indexing::BuildIndex(
          common::GetFileContents(common::GetFlagOrDie(FLAGS(text_input)))),
      common::GetFlagOrDie(FLAGS(index_path)));

  gflags::ShutDownCommandLineFlags();
  return 0;
}
