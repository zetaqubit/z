#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <snapshot_to_train_on>"
  exit 1
fi

srcTrainDir=~/hand_tracking/blaze_root/src/genesis/data/saved/lmdb/"$1"_train
srcTestDir=~/hand_tracking/blaze_root/src/genesis/data/saved/lmdb/"$1"_test

destTrainDir=~/hand_tracking/blaze_root/src/genesis/caffe/input/handnet_train_lmdb
destTestDir=~/hand_tracking/blaze_root/src/genesis/caffe/input/handnet_test_lmdb

rm -rf "$destTrainDir"
rm -rf "$destTestDir"

cp -rf "$srcTrainDir" "$destTrainDir"
cp -rf "$srcTestDir" "$destTestDir"
