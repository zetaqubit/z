#ifndef SRC_GENESIS_CAFFE_HAND_NEURAL_NET_H_
#define SRC_GENESIS_CAFFE_HAND_NEURAL_NET_H_

#include <string>

#include "src/genesis/visualization/image_viewer.h"
#include "src/third_party/caffe/include/caffe/caffe.hpp"

using caffe::Blob;
using caffe::Caffe;
using caffe::Net;
using caffe::Layer;
using caffe::vector;

namespace genesis {

class InferenceResult {
 public:
  bool has_hand;
};

class HandNeuralNet {
 public:
  HandNeuralNet(const std::string& model_prototxt,
                const std::string& weights_prototxt);

  // @param frame the data given to the first layer of the NN.
  InferenceResult RunInferenceOnFrame(const float* frame, int width,
                                      int height);

 private:
  Net<float> caffe_net_;

  ImageViewer debug_viewer_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_CAFFE_HAND_NEURAL_NET_H_
