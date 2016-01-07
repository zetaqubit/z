#include "src/genesis/visualization/gl_utils.h"

#include <fstream>
#include <cmath>

#include "src/third_party/glog/src/glog/logging.h"

using std::string;

namespace {

bool ReadFileContents(const string& filename, string* contents) {
  try {
    std::ifstream in;
    in.open(filename);

    if (!in) {
      LOG(ERROR) << "Unable to open " << filename << " for reading: " << errno;
      return false;
    }

    in.seekg(0, std::ios::end);
    contents->resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&((*contents)[0]), contents->size());
    in.close();
    return true;
  } catch (...) {
    LOG(ERROR) << "Caught generic exception.";
  }
  return false;
}

void LogShaderError(GLuint shader) {
  GLint max_length = 0;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

  // The max_length includes the NULL character
  std::vector<GLchar> error_log(max_length);
  glGetShaderInfoLog(shader, max_length, &max_length, error_log.data());
  LOG(ERROR) << error_log.data();
}

GLint CompileShader(GLenum shader_type, const string& source_filename) {
  string source;
  if (!ReadFileContents(source_filename, &source)) {
    LOG(ERROR) << "Could not read shader: " << source_filename;
    return -1;
  }

  GLuint shader = glCreateShader(shader_type);
  const GLchar* source_str = static_cast<const GLchar *>(source.c_str());
  glShaderSource(shader, 1, &source_str, NULL);
  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    LOG(ERROR) << "Unable to compile "
               << (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment")
               << "shader: " << status;
    LogShaderError(shader);
    return -1;
  }
  return shader;
}

}  // namespace

namespace genesis {

void AssertNoGlError(string msg) {
  GLenum err = glGetError();
  if (err != GL_NO_ERROR) {
    LOG(FATAL) << "GL error: " << err << " [" << msg << "]";
  }
}

GLint CreateProgram(const string& vertex_file, const string& fragment_file) {
  LOG(ERROR) << "Creating program.";
  GLint program = glCreateProgram();

  LOG(ERROR) << "Compiling vertex shader";
  GLint vertex_shader = CompileShader(GL_VERTEX_SHADER, vertex_file);

  LOG(ERROR) << "Compiling fragment shader";
  GLint fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragment_file);
  if (vertex_shader < 0 || fragment_shader < 0) {
    LOG(ERROR) << "Could not compile shader. Vertex: " << vertex_shader
        << ". Fragment: " << fragment_shader;
    return -1;
  }

  AssertNoGlError("After compiling shaders");

  LOG(ERROR) << "Attaching shaders.";
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);

  AssertNoGlError("After attaching shaders: ");

  LOG(ERROR) << "Linking program.";
  glLinkProgram(program);

  AssertNoGlError("After linking program: ");

  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    LOG(ERROR) << "Unable to link program: ";
    GLchar log[1024];
    GLsizei len;
    glGetProgramInfoLog(program, 1024, &len, log);
    LOG(ERROR) << "Error (length " << len << "): " << log;
    return -1;
  }

  return program;
}

GLuint CreateTextureReference() {
  GLuint texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  return texture_id;
}

void SetPerspectiveFrustum(
    GLdouble fov_y, GLdouble aspect, GLdouble near_plane, GLdouble far_plane) {
  GLdouble f_h = tan(fov_y * M_PI / 360) * near_plane;
  GLdouble f_w = f_h * aspect;
  glFrustum(-f_w, f_w, -f_h, f_h, near_plane, far_plane);
}

}  // namespace genesis
