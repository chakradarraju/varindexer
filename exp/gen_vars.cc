#include <fstream>
#include <gflags/gflags.h>
#include <iostream>

#include "common/file.h"
#include "common/flags.h"

DEFINE_string(words_path, "", "Path to words file.");
DEFINE_string(vars_path, "", "Path to output file.");
DEFINE_int32(n_vars, 1000000, "Number of vars to generate");

using std::cout;
using std::endl;
using std::string;

void GenerateVars(const string& vars_path, const std::vector<string>& words) {
  std::ofstream f(vars_path);
  srand (time(NULL));

  for (int i = 0; i < FLAGS_n_vars; i++) {
    int n_words = (rand() % 5) + 3;  // random number between 3 -> 7
    for (int j = 0; j < n_words; j++) {
      f << (j == 0 ? "" : "_") << words[rand() % words.size()];
    }
    int score = (rand() % 1000) + 1;  // random number between 1 -> 1000
    f << " " << score << endl;
  }
  f.close();
}

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  GenerateVars(
      common::GetFlagOrDie(FLAGS(vars_path)),
      common::GetFileContents(common::GetFlagOrDie(FLAGS(words_path))));

  gflags::ShutDownCommandLineFlags();
  return 0;
}
