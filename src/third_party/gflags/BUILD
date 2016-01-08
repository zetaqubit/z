cc_library(
  name = "gflags",
  srcs = glob([
    "src/**/*.cc",
  ], exclude = [
    "src/windows_port.cc",
  ]),
  hdrs = glob([
    "include/**/*.h",
  ], exclude = [
  ]),
  includes = [
    "include",
    "include/gflags",
  ],
  visibility = [
    "//visibility:public",
  ],
  linkopts = ["-pthread"],
)
