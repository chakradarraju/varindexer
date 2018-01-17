
#include <iostream>

#include "serving/rpc_client.h"

#include "include/grpc++/grpc++.h"
#include "serving/rpc_interface.grpc.pb.h"
#include "serving/rpc_interface.pb.h"

namespace serving {

using std::string;

VariableIndexClient::VariableIndexClient(const string& server_address)
  : stub_(serving::VariableIndex::NewStub(
      grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()))) {}

serving::SearchResult VariableIndexClient::Search(const string& query, const int n) const {
  serving::SearchRequest request;
  serving::SearchResult result;
  grpc::ClientContext context;
  request.set_query(query);
  if (n != 0) request.set_max_results(n);
  grpc::Status status = stub_->Search(&context, request, &result);

  if (!status.ok()) {
    std::cout << "Error during RPC (" << status.error_code() << "): " << status.error_message() << status.error_code() << std::endl;
  }
  return result;
}

}
