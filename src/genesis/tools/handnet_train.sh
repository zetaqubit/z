#!/bin/bash

~/hand_tracking/blaze_root/bazel-bin/src/third_party/caffe/tools/caffe train --solver=~/hand_tracking/blaze_root/src/genesis/caffe/handnet_solver.prototxt
