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
  linkopts = [
    "-lunwind",
  ],
  visibility = [
    "//visibility:public",
  ],
)
