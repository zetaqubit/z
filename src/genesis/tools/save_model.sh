#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <save_name>"
  exit 1
fi

ROOT=~/hand_tracking/blaze_root

# Input
caffeModel=$(ls -v $ROOT/data/genesis/caffe/model_snapshots/handnet_iter_*.caffemodel | tail -n 1)
solverState=$(ls -v $ROOT/data/genesis/caffe/model_snapshots/handnet_iter_*.solverstate | tail -n 1)
networkDefinition=$ROOT/src/genesis/caffe/handnet_*.prototxt

# Output dir
archiveDir=$ROOT/data/genesis/caffe/trained_models/"$1"

if [ -e "$archiveDir" ]; then
  echo "$archiveDir already exists"
  exit 1
fi

mkdir "$archiveDir"
cp $caffeModel "$archiveDir"
cp $solverState "$archiveDir"
ln -s $caffeModel "$archiveDir/handnet.caffemodel"
ln -s $solverState "$archiveDir/handnet.solverstate"
cp $networkDefinition "$archiveDir"
