#include "src/genesis/caffe/hand_neural_net.h"

#include "src/genesis/io/conversion_utils.h"
#include "src/third_party/caffe/include/caffe/solver.hpp"
#include "src/third_party/glog/src/glog/logging.h"

namespace genesis {

HandNeuralNet::HandNeuralNet(const std::string& solver_params,
                             const std::string& solver_snapshot)
    : debug_viewer_("CNN inference", 200, 200) {
  caffe::Caffe::set_mode(caffe::Caffe::GPU);

  // Create the solver with specified params.
  caffe::SolverParameter params;
  caffe::ReadProtoFromTextFileOrDie(solver_params, &params);
  solver_.reset(caffe::GetSolver<float>(params));

  // Load solver snapshot if specified.
  if (!solver_snapshot.empty()) {
    solver_->Restore(solver_snapshot.c_str());
  }
}

int MaxIndex(const std::vector<float>& data) {
  const float* a = data.data();
  return std::distance(a, std::max_element(a, a + data.size()));
}

void HandNeuralNet::LoadInputIntoNN(const Image& image,
                                    const proto::LeapFrame& ground_truth) {
  // Visualize the image.
  debug_viewer_.UpdateNormalized(image);

  // Load the input data.
  caffe::Net<float>* net = solver_->net().get();
  caffe::Blob<float>* image_blob = net->input_blobs()[0];
  float* image_cpu_data = image_blob->mutable_cpu_data();
  std::copy(image.begin(), image.end(), image_cpu_data);

  // Load hand ground truth.
  caffe::Blob<float>* hand_blob = net->input_blobs()[1];
  float* hand_cpu_data = hand_blob->mutable_cpu_data();
  std::vector<float> hand_gt;
  SerializeHand(ground_truth.left_hand(), &hand_gt);
  std::copy(hand_gt.begin(), hand_gt.end(), hand_cpu_data);

  // Load the label data.
  caffe::Blob<float>* label_blob = net->input_blobs()[2];
  float* label_cpu_data = label_blob->mutable_cpu_data();
  label_cpu_data[0] = ground_truth.has_left_hand() ? 1 : 0;
}

InferenceResult HandNeuralNet::ReadOutputFromNN(
    const proto::LeapFrame& ground_truth) {
  caffe::Net<float>* net = solver_->net().get();

  auto output_layer = net->blob_by_name("output");
  const float* begin = output_layer->cpu_data();
  const float* end = begin + output_layer->channels();
  auto result = std::vector<float>(begin, end);
  float predicted_x = result[0];
  float predicted_y = result[1];
  int max_index = MaxIndex(result);

  float actual_x = ground_truth.left_hand().palm().left_screen_coords().u();
  float actual_y = ground_truth.left_hand().palm().left_screen_coords().v();
  auto loss_layer = net->blob_by_name("loss");
  float loss = loss_layer->cpu_data()[0];
#if 0
  LOG(INFO) << "Predict: " << max_index
            << (actual_label_ == -1 ? "" : ". actual: ")
            << (actual_label_ == -1 ? "" : std::to_string(actual_label_))
            << ". prob: " << result[max_index]
            << ". loss: " << loss;
#else
  LOG(INFO) << Format("Pre [Act]: %7.4f|%7.4f || %7.4f|%7.4f ||" /* %7.4f[%7.4f]" */,
                      predicted_x, actual_x, predicted_y, actual_y
                      /* 0, 0 */)
            << ". loss: " << loss;
#endif

  debug_viewer_.DrawPoint(predicted_x, 1 - predicted_y, 4.0f);
  debug_viewer_.EndFrame();

  bool has_hand = (max_index == 1);
  return InferenceResult(has_hand, loss);
}

InferenceResult HandNeuralNet::Infer(const Image& image,
                                     const proto::LeapFrame& ground_truth) {
  LoadInputIntoNN(image, ground_truth);
  solver_->net()->ForwardPrefilled();
  return ReadOutputFromNN(ground_truth);
}

InferenceResult HandNeuralNet::Train(const Image& image,
                                     const proto::LeapFrame& ground_truth) {

  // Do a forward pass to check loss. Backprop only if loss is large enough.
  // This prevents the NN from being flooded with easy examples.
  InferenceResult result = Infer(image, ground_truth);
  if (result.loss < 0.001) {
    LOG(INFO) << "Loss is " << result.loss << ". Not training.";
    return result;
  }
  LOG(INFO) << "Training w/ loss = " << result.loss;

  LoadInputIntoNN(image, ground_truth);
  solver_->Step(1);
  return ReadOutputFromNN(ground_truth);
}

}  // namespace genesis
