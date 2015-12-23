#!/bin/bash

~/hand_tracking/blaze_root/bazel-bin/src/third_party/caffe/tools/caffe test --model=/home/z/hand_tracking/blaze_root/src/genesis/caffe/handnet_train_test.prototxt --weights=/home/z/hand_tracking/blaze_root/data/genesis/caffe/model_snapshots/handnet_iter_10000.caffemodel
