
load("@org_pubref_rules_protobuf//cpp:rules.bzl", "cc_proto_library")

cc_binary(
    name = "rpc_server",
    srcs = ["rpc_server.cc"],
    deps = [
        ":rpc_interface_proto",
        ":query_processor",
        "//common:flags",
        "//common:index",
        "//external:gflags",
        "@com_google_grpc//:grpc",
    ],
)

cc_proto_library(
    name = "rpc_interface_proto",
    protos = ["rpc_interface.proto"],
    with_grpc = True,
)

cc_library(
    name = "query_processor",
    srcs = ["query_processor.cc"],
    hdrs = ["query_processor.h"],
    deps = [
        "//common:index_proto",
    ],
)

cc_test(
    name = "query_processor_test",
    srcs = ["query_processor_test.cc"],
    deps = [
        ":query_processor",
        "//indexing:indexer",
        "@com_google_googletest//:gtest_main",
    ],
    size = "small",
)

cc_binary(
    name = "user_client",
    srcs = ["user_client.cc"],
    deps = [
        ":rpc_client",
        "//external:gflags",
    ],
)

cc_library(
    name = "rpc_client",
    srcs = ["rpc_client.cc"],
    hdrs = ["rpc_client.h"],
    deps = [
        ":rpc_interface_proto",
        "@com_google_grpc//:grpc",
    ],
)

cc_binary(
    name = "load_test",
    srcs = ["load_test.cc"],
    deps = [
        ":rpc_client",
        "//common:file",
        "//common:flags",
        "//external:gflags",
    ],
)
