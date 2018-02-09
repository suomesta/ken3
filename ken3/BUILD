cc_library(
    name = "stopwatch",
    srcs = ["stopwatch.cpp"],
    hdrs = ["stopwatch.hpp"],
    visibility = ["//unittest:__pkg__"],
)

cc_library(
    name = "pystr",
    srcs = ["pystr.cpp"],
    hdrs = ["pystr.hpp"],
    visibility = ["//unittest:__pkg__"],
)

cc_library(
    name = "metric",
    hdrs = ["metric.hpp"],
    visibility = ["//unittest:__pkg__"],
)

cc_binary(
    name = "test",
    srcs = ["test.cpp"],
    deps = [":stopwatch", ":pystr"],
)
