
cc_binary(
    name = "build_index",
    srcs = ["build_index.cc"],
    deps = [
        ":indexer",
        "//common:file",
        "//common:flags",
        "//external:gflags",
    ],
)

cc_library(
    name = "indexer",
    srcs = ["indexer.cc"],
    hdrs = ["indexer.h"],
    deps = [
        "//common:index_proto",
        "//external:gflags",
        "@com_google_absl//absl/strings",
    ],
    # We use this library to do end to end testing, ie build a index from text
    # input and run query on it. See //serving:query_processor_test
    visibility = ["//visibility:public"],  
)

cc_test(
    name = "indexer_test",
    srcs = ["indexer_test.cc"],
    deps = [
        ":indexer",
        "@com_google_googletest//:gtest_main",
    ],
)
