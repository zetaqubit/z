# Tools for proto compilation

def proto_library(name, srcs, deps=None, cc_api_version=None, visibility=None):
    """
    # my_proto.proto
    import "absolute/path/to/other.proto";

    message Foo {
        repeated namespace.Other other = 1;
    };

    # build file
    #load("//tools/protobuf/protobuf", "proto_library")

    proto_library(
        name = "foo_proto",
        srcs = ["foo.proto"],
        deps = ["//absolute/path/to/other_proto"]
    )
    """
    if not deps: deps = []

    # cc_api_version unused, maintain for compatibility with "real" proto_library

    hdrs = []
    ccs = []
    for p in srcs:
        #fail("Proto must end in \".proto\"", p, not p.endswith(".proto"))
        short_p = p.replace('.proto', '')
        hdrs += [short_p + '.pb.h']
        ccs += [short_p + '.pb.cc']

    # Bazel always runs these commands from the workspace root
    # To import protos,
    protogen_name = name + "_genprotoc"
    native.genrule(
                   name = protogen_name,
                   srcs = srcs,
                   outs = hdrs + ccs,
                   cmd = ("$(location //src/third_party/protobuf:protoc) " +
                          "--proto_path=. --cpp_out=$(GENDIR) $(SRCS)"),
                   tools = ["//src/third_party/protobuf:protoc"],
                   visibility = visibility,
                   )

    native.cc_library(
                      name = name,
                      hdrs = hdrs,
                      srcs = [ protogen_name ],
                      deps = ["//src/third_party/protobuf:protobuf"] + deps,
                      visibility = visibility)
