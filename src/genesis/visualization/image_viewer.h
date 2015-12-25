#ifndef SRC_GENESIS_VISUALIZATION_IMAGE_VIEWER_H_
#define SRC_GENESIS_VISUALIZATION_IMAGE_VIEWER_H_

#include <string>

#include "src/genesis/visualization/gl_window.h"
#include "src/genesis/visualization/texture_shader.h"

namespace genesis {

class ImageViewer {
 public:
  ImageViewer(const std::string& window_title, int win_width, int win_height);
  void Update(const uint8_t* data, int width, int height);
  void UpdateNormalized(const float* data, int width, int height);

 private:
  GlWindow window_;
  TextureShader shader_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_VISUALIZATION_IMAGE_VIEWER_H_
