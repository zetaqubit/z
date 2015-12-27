#include "src/genesis/caffe/hand_neural_net.h"

#include <glog/logging.h>

#include "src/genesis/io/conversion_utils.h"
#include "src/third_party/caffe/include/caffe/solver.hpp"

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

void HandNeuralNet::LoadInputIntoNN(const float* frame, int width, int height,
                                    int label) {
  // Normalize and visualize the frame.
  auto scaled = ConvertImageToNetInput(frame, width, height);
  debug_viewer_.UpdateNormalized(scaled.data(), 28, 28);

  // Load the frame data.
  caffe::Net<float>* net = solver_->net().get();
  caffe::Blob<float>* input_layer = net->input_blobs()[0];
  float* input_data = input_layer->mutable_cpu_data();
  for (int i = 0; i < 28 * 28; i++) {
    input_data[i] = scaled[i];
  }

  // Load the label data, if any.
  if (label != -1) {
    caffe::Blob<float>* input_label = net->input_blobs()[1];
    float* input_label_data = input_label->mutable_cpu_data();
    input_label_data[0] = label;
  }
}

InferenceResult HandNeuralNet::ReadOutputFromNN() {
  caffe::Net<float>* net = solver_->net().get();

  auto output_layer = net->blob_by_name("ip2");
  const float* begin = output_layer->cpu_data();
  const float* end = begin + output_layer->channels();
  auto result = std::vector<float>(begin, end);
  int max_index = MaxIndex(result);

  auto loss_layer = net->blob_by_name("loss");
  float loss = loss_layer->cpu_data()[0];
#if 1
  LOG(INFO) << "Predict: " << max_index
            << (actual_label_ == -1 ? "" : ". actual: ")
            << (actual_label_ == -1 ? "" : std::to_string(actual_label_))
            << ". prob: " << result[max_index]
            << ". loss: " << loss;
#endif

  bool has_hand = (max_index == 1);
  return InferenceResult(has_hand);
}

InferenceResult HandNeuralNet::Infer(const float* frame, int width, int height,
                                     int label) {
  actual_label_ = label;
  LoadInputIntoNN(frame, width, height, -1 /* label */);
  solver_->net()->ForwardPrefilled();
  return ReadOutputFromNN();
}

InferenceResult HandNeuralNet::Train(const float* frame, int width, int height,
                                     int label) {
  actual_label_ = label;
  LoadInputIntoNN(frame, width, height, label);
  solver_->Step(1);
  return ReadOutputFromNN();
}

}  // namespace genesis
