
load("@org_pubref_rules_protobuf//cpp:rules.bzl", "cc_proto_library")

cc_proto_library(
    name = "test_proto",
		protos = ["test.proto"],
		with_grpc = True,
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "grpc",
    srcs = ["grpc.cc"],
    deps = [
        ":test_proto",
        "@com_google_grpc//:grpc",
    ],
)

cc_binary(
    name = "gflags",
    srcs = ["gflags.cc"],
    deps = ["//external:gflags"],
)

cc_binary(
    name = "pq",
    srcs = ["pq.cc"],
    deps = [],
)

cc_binary(
    name = "gen_vars",
    srcs = ["gen_vars.cc"],
    deps = [
        "//common:file",
        "//common:flags",
        "//external:gflags",
    ],
)

cc_binary(
    name = "parse_proto",
    srcs = ["parse_proto.cc"],
    deps = [
        "//common:index",
        "//common:flags",
        "//external:gflags",
    ],
)

cc_binary(
    name = "gen_queries",
    srcs = ["gen_queries.cc"],
    deps = [
        "//common:file",
        "//common:flags",
        "//external:gflags",
    ],
)
