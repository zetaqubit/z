#ifndef SRC_GENESIS_VISUALIZATION_UNDISTORTED_TEXTURE_SHADER_H_
#define SRC_GENESIS_VISUALIZATION_UNDISTORTED_TEXTURE_SHADER_H_

#include <GL/glew.h>

namespace genesis {

class UndistortedTextureShader {
 public:
  bool Init();
  void UpdateRawTexture(const uint8_t* bytes, int width, int height);
  void UpdateDistortionTexture(const float* bytes, int width, int height);
  void Draw(float aspect_ratio);

 private:
  GLint program_;
  GLuint raw_texture_;
  GLuint distortion_texture_;

};

}  // namespace genesis

#endif  // SRC_GENESIS_VISUALIZATION_UNDISTORTED_TEXTURE_SHADER_H_
