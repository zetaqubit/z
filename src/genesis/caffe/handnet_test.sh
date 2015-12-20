#!/bin/bash

~/hand_tracking/blaze_root/bazel-bin/src/third_party/caffe/tools/caffe test --model=handnet_train_test.prototxt --weights=snapshots/handnet_iter_10000.caffemodel
