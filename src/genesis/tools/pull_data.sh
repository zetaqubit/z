#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <snapshot_to_train_on>"
  exit 1
fi

ROOT=~/hand_tracking/blaze_root

srcTrainDir="$ROOT"/data/genesis/saved/lmdb/"$1"_train
srcTestDir="$ROOT"/data/genesis/saved/lmdb/"$1"_test

destTrainDir="$ROOT"/data/genesis/caffe/handnet_train_lmdb
destTestDir="$ROOT"/data/genesis/caffe/handnet_test_lmdb

if [ ! -e "$srcTrainDir" ]; then
  echo "$srcTrainDir does not exist"
  exit 1
fi

if [ ! -e "$srcTestDir" ]; then
  echo "$srcTestDir does not exist"
  echo "Using training set as test set: $srcTrainDir"
  srcTestDir="$srcTrainDir"
fi

rm -rf "$destTrainDir"
rm -rf "$destTestDir"

cp -rf "$srcTrainDir" "$destTrainDir"
cp -rf "$srcTestDir" "$destTestDir"

# TODO: enable if need to do mean subtract.
#rm "$destTrainDir"_mean.binaryproto
#rm "$destTestDir"_mean.binaryproto
#"$ROOT"/src/third_party/caffe/build/tools/compute_image_mean "$destTrainDir"{,_mean.binaryproto}
#"$ROOT"/src/third_party/caffe/build/tools/compute_image_mean "$destTestDir"{,_mean.binaryproto}
