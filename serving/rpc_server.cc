// Runs a RPC server that implements service defined in rpc_interface.proto.
// Uses index built using indexing/build_index.cc.
//
// Usage:
// bazel build serving:rpc_server -c opt && bazel-bin/serving/rpc_server \
// --index_path=$BASE/data/index

#include <gflags/gflags.h>
#include <sstream>
#include <fstream>

#include "common/flags.h"
#include "common/index.h"
#include "include/grpc++/grpc++.h"
#include "serving/query_processor.h"
#include "serving/rpc_interface.grpc.pb.h"
#include "serving/rpc_interface.pb.h"

DEFINE_string(server_address, "0.0.0.0:50051", "Address where RPC server will listen.");
DEFINE_string(index_path, "", "Path to read index from.");

using grpc::ServerContext;
using grpc::Status;
using grpc::ServerBuilder;
using grpc::Server;
using std::cout;
using std::endl;
using std::string;

namespace serving {

class VariableIndexImpl : public serving::VariableIndex::Service {
 public:
  VariableIndexImpl(const string& index_path) : processor_(common::ReadIndexOrDie(index_path)) {}

 private:
  Status Search(ServerContext* context, const SearchRequest* request, SearchResult* result) override {
    for (const string& variable : processor_.Search(request->query(), request->max_results())) {
      result->add_variable(variable);
    }
    return Status::OK;
  }
  const serving::QueryProcessor processor_;
};

void RunServer(const string& server_address, const string& index_path) {
  VariableIndexImpl service(index_path);

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

}  // namespace serving

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  serving::RunServer(
      FLAGS_server_address, common::GetFlagOrDie(FLAGS(index_path)));

  gflags::ShutDownCommandLineFlags();
  return 0;
}
