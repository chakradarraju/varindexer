
#include <memory>

#include "serving/rpc_interface.grpc.pb.h"
#include "serving/rpc_interface.pb.h"

namespace serving {

// Creates a stub to RPC server at passed server address and helps querying it.
// Thread safe.
class VariableIndexClient {
 public:
  VariableIndexClient(const std::string& server_address);

  // Issues Search RPC to connected server and returns SearchResult.
  // Logs error to stdout.
  serving::SearchResult Search(const std::string& query, const int n = 0) const;
 
 private:
  std::unique_ptr<serving::VariableIndex::Stub> stub_;
};

}  // namespace serving
