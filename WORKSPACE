
local_repository(
		name = "org_pubref_rules_protobuf",
		path = "../src/rules_protobuf-0.8.1",
)

local_repository(
    name = "com_github_gflags_gflags",
    path = "../src/gflags-2.2.1",
)

local_repository(
    name = "com_google_absl",
    path = "../src/abseil-cpp-master",
)

bind(
    name = "gflags",
    actual = "@com_github_gflags_gflags//:gflags",
)

load("@org_pubref_rules_protobuf//cpp:rules.bzl", "cpp_proto_repositories")
cpp_proto_repositories()

