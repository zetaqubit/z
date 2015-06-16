#include "src/genesis/gl_utils.h"

#include <fstream>

#include <glog/logging.h>

using std::string;

namespace genesis {

GLint CreateProgram(const string& vertex_file, const string& fragment_file) {
  LOG(ERROR) << "Creating program: error state: " << glGetError();

  GLint program = glCreateProgram();

  LOG(ERROR) << "Compiling vertex shader";

  GLint vertex_shader = CompileShader(GL_VERTEX_SHADER, vertex_file);

  LOG(ERROR) << "Compiling fragment shader";

  GLint fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragment_file);
  if (vertex_shader < 0 || fragment_shader < 0) {
    return -1;
  }

  LOG(ERROR) << "Attaching shaders.";

  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);

  LOG(ERROR) << "Linking program.";

  glLinkProgram(program);
  GLint status;
  glGetProgramiv(program, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    LOG(ERROR) << "Unable to link program.";
    return -1;
  }

  return program;
}

GLint CompileShader(GLenum shader_type, const string& source_filename) {
  string source;
  if (!ReadFileContents(source_filename, &source)) {
    return -1;
  }

  GLuint shader = glCreateShader(shader_type);
  const GLchar* source_str = static_cast<const GLchar *>(source.c_str());
  glShaderSource(shader, 1, &source_str, NULL);
  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    LOG(ERROR) 
        << "Unable to compile "
        << (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
        << "shader: " << status;
    return -1;
  }
  return shader;
}

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

}  // namespace genesis
