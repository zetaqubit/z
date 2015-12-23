#include "src/genesis/visualization/undistorted_texture_shader.h"

#include <glog/logging.h>
#include <string>

#include "src/genesis/visualization/gl_utils.h"

namespace {

static const std::string kVertexShaderFile =
    "src/genesis/visualization/shaders/passthrough.vert";
static const std::string kFragmentShaderFile =
    "src/genesis/visualization/shaders/texture_undistort.frag";

}  // namespace

namespace genesis {

bool UndistortedTextureShader::Init() {
  // Create the program.
  program_ = CreateProgram(kVertexShaderFile, kFragmentShaderFile);
  if (program_ < 0) {
    return false;
  }
  glUseProgram(program_);
  GLuint raw_sampler = glGetUniformLocation(program_, "rawTexture");
  GLuint distortion_sampler = glGetUniformLocation(program_, "distortionTexture");
  glUniform1i(raw_sampler, 0);
  glUniform1i(distortion_sampler, 1);

  // Create the textures.
  raw_texture_ = CreateTextureReference();
  distortion_texture_ = CreateTextureReference();

  return true;
}

void UndistortedTextureShader::UpdateRawTexture(const uint8_t* bytes,
                                                int width, int height) {
  glBindTexture(GL_TEXTURE_2D, raw_texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0,
      GL_RED, GL_UNSIGNED_BYTE, bytes);
}

void UndistortedTextureShader::UpdateDistortionTexture(
    const float* bytes, int width, int height) {
  glBindTexture(GL_TEXTURE_2D, distortion_texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width,
      height, 0, GL_RG, GL_FLOAT, bytes);
}

void UndistortedTextureShader::Draw(float aspect_ratio) {
  glEnable(GL_TEXTURE_2D);
  glUseProgram(program_);
  AssertNoGlError("glUseProgram");

  // Draw the left image.
  glActiveTexture(GL_TEXTURE0);
  AssertNoGlError("glActiveTexture");
  glBindTexture(GL_TEXTURE_2D, raw_texture_);
  AssertNoGlError("glBindTexture");
  glActiveTexture(GL_TEXTURE1);
  AssertNoGlError("glActiveTexture");
  glBindTexture(GL_TEXTURE_2D, distortion_texture_);
  AssertNoGlError("glBindTexture");
  glBegin(GL_QUADS);
  float a = 1 / aspect_ratio;
  glTexCoord2f(0.f, 1.f); glVertex3f(-1.f,  a, 0.f); // Top Left
  glTexCoord2f(1.f, 1.f); glVertex3f( 1.f,  a, 0.f); // Top Right
  glTexCoord2f(1.f, 0.f); glVertex3f( 1.f, -a, 0.f); // Bottom Right
  glTexCoord2f(0.f, 0.f); glVertex3f(-1.f, -a, 0.f); // Bottom Left
  glEnd();
  AssertNoGlError("After drawing quad");

}

}  // namespace genesis
