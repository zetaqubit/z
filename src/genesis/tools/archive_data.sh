#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <save_directory>"
  exit 1
fi

destProtoDir=~/hand_tracking/blaze_root/data/genesis/saved/proto/"$1"
destLmdbDir=~/hand_tracking/blaze_root/data/genesis/saved/lmdb/"$1"

rm -rif "$destProtoDir"
rm -rif "$destLmdbDir"

mv ~/hand_tracking/blaze_root/data/genesis/current/proto "$destProtoDir"
mv ~/hand_tracking/blaze_root/data/genesis/current/lmdb "$destLmdbDir"
