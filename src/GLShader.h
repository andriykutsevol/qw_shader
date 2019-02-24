/*
 * GLShader.h
 *
 *  Created on: 29 апр. 2015 г.
 *      Author: andrey
 */

#include "head.h"

using std::string;
using namespace glm;

class GlShader
{
public:

  GlShader();

  ~GlShader();

  GLuint loadFiles(const string& vertex_file_name, const string& fragment_file_name);
  GLuint load(const string& vertex_source, const string& fragment_source);
  GLuint load(const GLchar* vertex_source, const GLchar* fragment_source);

  void use();

  GLuint getIDProgram() { return ShaderProgram; }

  bool isLoad() { return ShaderProgram != 0; }

  //! Attribute
  GLint getAttribLocation(const GLchar* name) const;
  GLint getAttribLocation(const std::string& name) const;
  //! Uniform get
  GLint getUniformLocation(const GLchar* name) const;
  GLint getUniformLocation(const std::string& name) const;
  //! Uniform set
  void setUniform(GLint location, const vec4& value);
  void setUniform(GLint location, const vec3& value);
  void setUniform(GLint location, const vec2& value);

  void setUniform(GLint location, const mat4& value);
  void setUniform(GLint location, const GLint value);

  //------------------------------------------
  // Subrotines

  GLint GetSubroutineIndex(const GLchar*name) const;
  GLint GetSubroutineIndex(const std::string& name) const;
  void UniformSubroutinesuiv(const GLuint *location);

  GLint GetSubroutineIndexF(const GLchar*name) const;
  GLint GetSubroutineIndexF(const std::string& name) const;
  void UniformSubroutinesuivF(const GLuint *location);





private:
  //! Функции печати лога шейдера
  void printInfoLogShader(GLuint shader);
  //! Функция печати лога шейдерной программы
  void printInfoLogProgram(GLuint shader);

  GLuint loadSourcefile(const string& source_file_name, GLuint shader_type);

  GLuint compileSource(const GLchar* source, GLuint shader_type);

  void linkProgram();


  GLuint ShaderProgram;
  GLuint vertex_shader;
  GLuint fragment_shader;
};

