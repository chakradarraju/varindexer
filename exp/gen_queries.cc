#include <fstream>
#include <gflags/gflags.h>
#include <iostream>

#include "common/file.h"
#include "common/flags.h"

DEFINE_string(words_path, "", "Path to words file.");
DEFINE_string(queries_path, "", "Path to output file.");
DEFINE_int32(n_queries, 100000, "Number of vars to generate");

using std::cout;
using std::endl;
using std::string;

void GenerateQueries(const string& queries_path, const std::vector<string>& words) {
  if (words.size() < 1) return;
  std::ofstream f(queries_path);
  srand (time(NULL));

  for (int i = 0; i < FLAGS_n_queries; i++) {
    const string& word = words[rand() % words.size()];
    if (word.size() < 1) continue;
    const int prefix_len = rand() % word.size();
    f << word.substr(0, prefix_len + 1) << endl;
  }
  f.close();
}

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  GenerateQueries(
      common::GetFlagOrDie(FLAGS(queries_path)),
      common::GetFileContents(common::GetFlagOrDie(FLAGS(words_path))));

  gflags::ShutDownCommandLineFlags();
  return 0;
}
