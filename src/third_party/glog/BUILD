cc_library(
  name = "glog",
  srcs = glob([
    "src/**/*.cc",
  ], exclude = [
    "src/**/*test*.cc",
    "src/windows/**",
  ]),
  hdrs = glob([
    "src/**/*.h",
  ], exclude = [
    "src/windows/**",
  ]),
  includes = [
    "src/",
  ],
  deps = [
    "//src/third_party/gflags",
  ],
  linkopts = [
    "-lunwind",
  ],
  visibility = [
    "//visibility:public",
  ],
)
