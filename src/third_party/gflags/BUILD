cc_library(
  name = "gflags",
  srcs = glob([
    "src/**/*.cc",
  ], exclude = [
    "src/gflags_completions.cc",
    "src/windows_port.cc",
  ]),
  hdrs = glob([
    "include/**/*.h",
  ], exclude = [
    "include/gflags/gflags_completions.h",
  ]),
  includes = [
    "include/gflags",
  ],
  visibility = [
    "//visibility:public",
  ],
)
