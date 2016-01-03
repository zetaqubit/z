#ifndef SRC_GENESIS_CAFFE_HAND_NEURAL_NET_H_
#define SRC_GENESIS_CAFFE_HAND_NEURAL_NET_H_

#include <string>

#include "src/genesis/io/datatypes.h"
#include "src/genesis/io/proto/leap_frame.pb.h"
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
  // @param ground_truth the ground truth label/pose
  //        (used only for debug output).
  InferenceResult Infer(const Image& image,
                        const proto::LeapFrame& ground_truth);

  // Trains the NN using |frame| and its corresponding ground truth label.
  // @param frame the data given to the first layer of the NN.
  // @param ground_truth the ground truth label/pose for the NN to learn
  InferenceResult Train(const Image& image,
                        const proto::LeapFrame& ground_truth);

 private:
  // Loads the image frame and ground truth into the bottom layers of the NN.
  void LoadInputIntoNN(const Image& image,
                       const proto::LeapFrame& ground_truth);
  InferenceResult ReadOutputFromNN(const proto::LeapFrame& ground_truth);

  std::unique_ptr<caffe::Solver<float> > solver_;
  ImageViewer debug_viewer_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_CAFFE_HAND_NEURAL_NET_H_
