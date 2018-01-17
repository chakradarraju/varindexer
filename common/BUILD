
load("@org_pubref_rules_protobuf//cpp:rules.bzl", "cc_proto_library")

package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "file",
    srcs = ["file.cc"],
    hdrs = ["file.h"],
    deps = [":index_proto"],
)

cc_library(
    name = "index",
    srcs = ["index.cc"],
    hdrs = ["index.h"],
    deps = [":index_proto"],
)

cc_proto_library(
    name = "index_proto",
		protos = ["index.proto"],
)

cc_library(
    name = "flags",
    srcs = ["flags.cc"],
    hdrs = ["flags.h"],
)
