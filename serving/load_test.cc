
#include <vector>
#include <fstream>
#include <iostream>
#include <gflags/gflags.h>

#include "serving/rpc_client.h"
#include "common/file.h"
#include "common/flags.h"

DEFINE_string(server_address, "0.0.0.0:50051", "Address of RPC server to connect.");
DEFINE_string(words_path, "", "Path to words file.");
DEFINE_int32(n_queries, 100000, "Number of vars to generate");
DEFINE_string(output_path, "", "Path to file to write output to.");
DEFINE_bool(output, true, "Whether to output");

using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  srand (time(NULL));

  std::ofstream f;
  if (FLAGS_output) f.open(common::GetFlagOrDie(FLAGS(output_path)));
  serving::VariableIndexClient client(FLAGS_server_address);
  const auto words = common::GetFileContents(common::GetFlagOrDie(FLAGS(words_path)));
  for (int i = 0; i < FLAGS_n_queries; i++) {
    const string& word = words[rand() % words.size()];
    const int prefix_len = rand() % word.size();
    const string query = word.substr(0, prefix_len + 1);
    if (FLAGS_output) f << query << std::endl;
    const auto result = client.Search(query);
    for (const auto& variable : result.variable()) {
      if (FLAGS_output) f << "╠" << variable << std::endl;
    }
  }
  f.close();

  gflags::ShutDownCommandLineFlags();
  return 0;
}
