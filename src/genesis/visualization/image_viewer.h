#ifndef SRC_GENESIS_VISUALIZATION_IMAGE_VIEWER_H_
#define SRC_GENESIS_VISUALIZATION_IMAGE_VIEWER_H_

#include <string>

#include "src/genesis/io/datatypes.h"
#include "src/genesis/visualization/gl_window.h"
#include "src/genesis/visualization/texture_shader.h"

namespace genesis {

class ImageViewer {
 public:
  ImageViewer(const std::string& window_title, int win_width, int win_height);

  // Displays an image in range [0, 256).
  void Update(const Image& image);

  // Displays an image in range (-1, 1).
  void UpdateNormalized(const Image& image);

 private:
  GlWindow window_;
  TextureShader shader_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_VISUALIZATION_IMAGE_VIEWER_H_
