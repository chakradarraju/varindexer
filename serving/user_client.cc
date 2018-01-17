// Runs a client that user can query and see response from RPC server run using serving/rpc_server.cc.
//
// Usage:
// bazel run serving:user_client -c opt

#include <gflags/gflags.h>

#include "serving/rpc_client.h"

DEFINE_string(server_address, "0.0.0.0:50051", "Address of RPC server to connect.");

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  serving::VariableIndexClient client(FLAGS_server_address);

  while (true) {
    std::string query;
    std::cin >> query;
    const auto result = client.Search(query);
    for (const auto variable : result.variable()) std::cout << "╠" << variable << std::endl;
  }

  gflags::ShutDownCommandLineFlags();
  return 0;
}
