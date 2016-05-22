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
    # Shard files to prevent out of memory.
    num_files = len(srcs)
    files_per_shard = 1
    for i in range(0, num_files, files_per_shard):
        gen_name = name + "_nvcc_" + str(i / files_per_shard)
        srcs_i = srcs[i:min(i + files_per_shard, num_files)]
        outs_i = outs[i:min(i + files_per_shard, num_files)]
        cmd_str = " & ".join([
            "$(location //src/third_party/cuda:nvcc)" +
            " -ccbin=$(location g++_wrapper)" +
            " " + " ".join(nvcc_opts) +
            " -c $(location " + s + ")" +
            " -o $(location " + o + ")"
            for s, o in zip(srcs_i, outs_i)
        ])
        native.genrule(
            name = gen_name,
            srcs = srcs_i + other_srcs,
            outs = outs_i,
            cmd = cmd_str,
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
