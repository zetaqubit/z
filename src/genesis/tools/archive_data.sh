#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <save_directory>"
  exit 1
fi

srcProtoDir=~/hand_tracking/blaze_root/data/genesis/current/proto
srcLmdbDir=~/hand_tracking/blaze_root/data/genesis/current/lmdb
destProtoDir=~/hand_tracking/blaze_root/data/genesis/saved/proto/"$1"
destLmdbDir=~/hand_tracking/blaze_root/data/genesis/saved/lmdb/"$1"

if [ ! -e "$srcProtoDir" ]; then
  echo "$srcProtoDir does not exist"
  exit 1
fi

if [ ! -e "$srcLmdbDir" ]; then
  echo "$srcLmdbDir does not exist"
  exit 1
fi

if [ -e "$destProtoDir" ]; then
  echo "$destProtoDir already exists"
  exit 1
fi

if [ -e "$destLmdbDir" ]; then
  echo "$destLmdbDir already exists"
  exit 1
fi

rm -rf "$destProtoDir"
rm -rf "$destLmdbDir"

mv "$srcProtoDir" "$destProtoDir"
mv "$srcLmdbDir" "$destLmdbDir"
