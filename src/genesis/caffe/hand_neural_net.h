#ifndef SRC_GENESIS_CAFFE_HAND_NEURAL_NET_H_
#define SRC_GENESIS_CAFFE_HAND_NEURAL_NET_H_

#include <string>

#include "src/genesis/io/datatypes.h"
#include "src/genesis/visualization/image_viewer.h"
#include "src/third_party/caffe/include/caffe/caffe.hpp"

namespace genesis {

class InferenceResult {
 public:
  InferenceResult(bool has_hand, float loss) {
    this->has_hand = has_hand;
    this->loss = loss;
  };

  bool has_hand;
  float loss;
};

class HandNeuralNet {
 public:
  HandNeuralNet(const std::string& solver_params,
                const std::string& solver_snapshot = "");

  // Infers the classification of |frame|. Does not train NN.
  //
  // @param frame the data given to the first layer of the NN.
  // @param label the ground truth label (used only for debug output).
  InferenceResult Infer(const Image& image, int label);

  // Trains the NN using |frame| and its corresponding ground truth label.
  // @param frame the data given to the first layer of the NN.
  // @param label ground truth label for the NN to learn
  InferenceResult Train(const Image& image, int label);

 private:
  // Loads the image frame and label (if any) into the bottom layers of the NN.
  void LoadInputIntoNN(const Image& image, int label);
  InferenceResult ReadOutputFromNN();

  std::unique_ptr<caffe::Solver<float> > solver_;

  ImageViewer debug_viewer_;
  int actual_label_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_CAFFE_HAND_NEURAL_NET_H_
