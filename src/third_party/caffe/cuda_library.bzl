def cuda_library(name, srcs, other_srcs=None, nvcc_opts=None, visibility=None):
    """
    @param srs .cu cuda sources to be compiled
    @param other_srcs non-cu sources (e.g. .h) that srcs depends on
    @param nvcc_opts options passed to nvcc
    """

    if not other_srcs: other_srcs = []
    if not nvcc_opts: nvcc_opts = []

    outs = []  # .o output files from nvcc
    for p in srcs:
        out = p.replace('.cu', '.o')
        outs += [out]

    # Bazel always runs these commands from the workspace root
    gen_name = name + "_nvcc"
    native.genrule(
        name = gen_name,
        srcs = srcs + other_srcs,
        outs = outs,
        cmd = " & ".join([
            "$(location //src/third_party/cuda:nvcc)" +
            " -ccbin=$(location g++_wrapper)" +
            " " + " ".join(nvcc_opts) +
            " -c $(location " + s + ")" +
            " -o $(location " + o + ")"
            for s, o in zip(srcs, outs)
          ]
        ),
        tools = [
          "g++_wrapper",
          "//src/third_party/cuda:nvcc",
        ],
        visibility = visibility,
        )

    native.cc_library(
        name = name,
        srcs = outs,
    )
