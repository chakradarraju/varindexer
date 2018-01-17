#include <iostream>
#include "exp/test.pb.h"
#include "exp/test.grpc.pb.h"
#include "include/grpc++/grpc++.h"

using grpc::Status;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using std::cout;
using std::endl;

Test GetTest() {
  Test a;
  a.set_field1("chakra");
  a.set_field2(2);
  return a;
}

class DummyImpl : public Dummy::Service {
  Status Trpc(ServerContext* context, const Test* request, Test* reply) {
    cout << "Running RPC" << endl;
    return {};
	}
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  DummyImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main() {
  auto a = GetTest();
  cout << a.field1() << " " << a.field2() << endl;

  RunServer();

  return 0;
}
