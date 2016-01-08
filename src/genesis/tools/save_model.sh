#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <save_name>"
  exit 1
fi

ROOT=~/hand_tracking/blaze_root

# Input
INPUT_SNAPSHOT_DIR=data/genesis/caffe/model_snapshots
INPUT_MODEL_DIR=src/genesis/caffe
caffeModel=$(ls -v $ROOT/$INPUT_SNAPSHOT_DIR/handnet_iter_*.caffemodel | tail -n 1)
solverState=$(ls -v $ROOT/$INPUT_SNAPSHOT_DIR/handnet_iter_*.solverstate | tail -n 1)
networkDefinition=$ROOT/$INPUT_MODEL_DIR/handnet*.prototxt

# Output dir
OUTPUT_SNAPSHOT_DIR=data/genesis/caffe/trained_models/"$1"
archiveDir=$ROOT/$OUTPUT_SNAPSHOT_DIR

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

# Fix path references in *.solver.prototxt
sed -i -e "s:$INPUT_SNAPSHOT_DIR:$OUTPUT_SNAPSHOT_DIR:g" $archiveDir/*.solver.prototxt
sed -i -e "s:$INPUT_MODEL_DIR:$OUTPUT_SNAPSHOT_DIR:g" $archiveDir/*.solver.prototxt
