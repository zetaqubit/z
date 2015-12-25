#include "src/genesis/caffe/hand_neural_net.h"

#include <glog/logging.h>

#include "src/genesis/io/conversion_utils.h"

namespace genesis {

HandNeuralNet::HandNeuralNet(const std::string& model_prototxt,
                             const std::string& weights_prototxt)
    : caffe_net_(model_prototxt, caffe::TEST),
      debug_viewer_("Image sent to NN", 200, 200) {

  Caffe::set_mode(Caffe::GPU);
  caffe_net_.CopyTrainedLayersFrom(weights_prototxt);
}

int MaxIndex(const std::vector<float>& data) {
  const float* a = data.data();
  return std::distance(a, std::max_element(a, a + data.size()));
}

// @param frame the data given to the first layer of the NN.
InferenceResult HandNeuralNet::RunInferenceOnFrame(const float* frame,
                                                   int width, int height) {
  Blob<float>* input_layer = caffe_net_.input_blobs()[0];

#if 0
  LOG(INFO) << "Input layer dim: (c h w): " << input_layer->channels() << "x"
      << input_layer->height() << "x" << input_layer->width()
      << ". Num inputs: " << caffe_net_.num_inputs()
      << ". Num outputs: " << caffe_net_.num_outputs()
  ;
#endif

  // TODO: Necessary to reshape?
  //input_layer->Reshape(1, 1 /* num_channels */, 28, 28);
  //caffe_net_.Reshape();

  auto scaled = ConvertImageToNetInput(frame, width, height);

  debug_viewer_.UpdateNormalized(scaled.data(), 28, 28);

  float* input_data = input_layer->mutable_cpu_data();
  for (int i = 0; i < 28 * 28; i++) {
    input_data[i] = scaled[i];
  }

  float loss = 0;
  const vector<Blob<float>*>& result = caffe_net_.ForwardPrefilled(&loss);
  const float* result_vec = result[0]->cpu_data();

  Blob<float>* output_layer = caffe_net_.output_blobs()[0];
  const float* begin = output_layer->cpu_data();
  const float* end = begin + output_layer->channels();
  auto result_new = std::vector<float>(begin, end);

  int max_index = MaxIndex(result_new);
  LOG(INFO) << "Predicted class: " << max_index << " (prob "
      << result_new[max_index] << ")";

#if 0
  LOG(INFO) << "Inference result: size: " << result_new.size()
      << ". [0]: " << result_new[0]
      << ". [1]: " << result_new[1]
  ;

  LOG(INFO) << "Inference result: size: " << result.size()
      << ". [0]: " << result[0]->shape_string()
      << ". [0][0]: " << std::to_string(result_vec[0]);
#endif
  return InferenceResult();
}

}  // namespace genesis
