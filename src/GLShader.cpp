/*
 * GLShader.cpp
 *
 *  Created on: 29 апр. 2015 г.
 *      Author: andrey
 */


#include "GLShader.h"
#include "head.h"

GlShader::GlShader():ShaderProgram(0)
{

}

GlShader::~GlShader()
{
  glUseProgram(0);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  glDeleteProgram(ShaderProgram);
}

GLuint GlShader::loadFiles(const string& vertex_file_name,const string& fragment_file_name)
{
  vertex_shader = loadSourcefile(vertex_file_name, GL_VERTEX_SHADER);
  fragment_shader = loadSourcefile(fragment_file_name, GL_FRAGMENT_SHADER);

  linkProgram();

  return ShaderProgram;
}

GLuint GlShader::load(const string& vertex_source,const string& fragment_source)
{
  vertex_shader   = compileSource(vertex_source.c_str(), GL_VERTEX_SHADER);
  fragment_shader = compileSource(fragment_source.c_str(), GL_FRAGMENT_SHADER);

  linkProgram();
  return ShaderProgram;
}

GLuint GlShader::load(const GLchar* vertex_source, const GLchar* fragment_source)
{
  vertex_shader   = compileSource(vertex_source, GL_VERTEX_SHADER);
  fragment_shader = compileSource(fragment_source, GL_FRAGMENT_SHADER);

  linkProgram();
  return ShaderProgram;
}

void GlShader::linkProgram()
{
  GLint link_ok = GL_FALSE;
  if(!vertex_shader || !fragment_shader)
  {
    ShaderProgram = GL_FALSE;
    return;
  }

  ShaderProgram = glCreateProgram();
  glAttachShader(ShaderProgram, vertex_shader);
  glAttachShader(ShaderProgram, fragment_shader);

  glLinkProgram(ShaderProgram);
  glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    std::cout<<"glLinkProgram:";
    #ifdef _DEBUG
      printInfoLogProgram(ShaderProgram);
    #endif
    ShaderProgram = GL_FALSE;
    return;
  }
}

void GlShader::use()
{
  glUseProgram(ShaderProgram);
}

//---------------------------------------------------

//! Attribute get
GLint GlShader::getAttribLocation(const GLchar* name) const
{
  GLint location = -1;
  location = glGetAttribLocation(ShaderProgram, name);
  if (location == -1)
    std::cout<<"Could not bind attribute "<<name<<"\n";
  return location;
}

GLint GlShader::getAttribLocation(const std::string& name) const
{
  return getAttribLocation(name.c_str());
}

//! Uniform get
GLint GlShader::getUniformLocation(const GLchar* name) const
{
  GLint location = -1;
  location = glGetUniformLocation(ShaderProgram, name);
  if (location == -1)
    std::cout<<"Could not bind uniform "<<name<<"\n";
  return location;
}

GLint GlShader::getUniformLocation(const std::string& name) const
{
  return getUniformLocation(name.c_str());
}
//---------------------------------------------------

//! Set Uniform
void GlShader::setUniform(GLint location, const vec4& value)
{
  glUniform4fv(location, 1, &value[0]);
}
void GlShader::setUniform(GLint location, const vec3& value)
{
  glUniform3fv(location, 1, &value[0]);
}
void GlShader::setUniform(GLint location, const vec2& value)
{
  glUniform2fv(location, 1, &value[0]);
}

void GlShader::setUniform(GLint location, const mat4& value)
{
  glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}
void GlShader::setUniform(GLint location, const GLint value)
{
  glUniform1i(location, value);
}
//---------------------------------------------------

//! Print info log
void GlShader::printInfoLogShader(GLuint shader)
{
  int infologLen = 0;
  int charsWritten  = 0;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);

  if (infologLen > 1)
  {
    GLchar *infoLog = new GLchar[infologLen];
    if (infoLog == NULL)
    {
      std::cout<<"ERROR: Could not allocate InfoLog buffer\n";
      exit(1);
    }
    glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);

    std::cout<<"InfoLog: "<<infoLog<<"\n\n\n";
    delete [] infoLog;
  }
}

//! Print info log
void GlShader::printInfoLogProgram(GLuint shader)
{
  int infologLen = 0;
  int charsWritten  = 0;

  glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infologLen);

  if (infologLen > 1)
  {
    GLchar *infoLog = new GLchar[infologLen];
    if (infoLog == NULL)
    {
      std::cout<<"ERROR: Could not allocate InfoLog buffer\n";
      exit(1);
    }
    glGetProgramInfoLog(shader, infologLen, &charsWritten, infoLog);

    std::cout<<"InfoLog: "<<infoLog<<"\n\n\n";
    delete [] infoLog;
  }
}

GLuint GlShader::compileSource(const GLchar* source, GLuint shader_type)
{
  GLuint shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  #ifdef _DEBUG
    printInfoLogShader(shader);
  #endif
  return shader;
}

GLuint GlShader::loadSourcefile(const string& source_file_name, GLuint shader_type)
{
  std::ifstream  file(source_file_name.c_str());
  if(!file)
  {
    std::cout<<source_file_name<<"  file  not  found\n";
    return  GL_FALSE;
  }

  std::istreambuf_iterator<char>  begin(file),  end;
        string  sourceStr(begin,  end);
  file.close();
  return  compileSource(sourceStr.c_str(),  shader_type);
}




//-------------------------------------------------------------------------
// Subrotines -------------------------------------------------------------


GLint GlShader::GetSubroutineIndex(const std::string& name) const
{
  return GetSubroutineIndex(name.c_str());
}

GLint GlShader::GetSubroutineIndex(const GLchar* name) const
{
  GLint location = -1;
  location = glGetSubroutineIndex(ShaderProgram, GL_VERTEX_SHADER, name);
  if (location == -1)
    std::cout<<"Could not bind attribute "<<name<<"\n";
  return location;
}



void GlShader::UniformSubroutinesuiv(const GLuint *location)
{

	glUniformSubroutinesuiv( GL_VERTEX_SHADER, 1, location);

}

//----------------------------
//----------------------------

GLint GlShader::GetSubroutineIndexF(const std::string& name) const
{
  return GetSubroutineIndexF(name.c_str());
}

GLint GlShader::GetSubroutineIndexF(const GLchar* name) const
{
  GLint location = -1;
  location = glGetSubroutineIndex(ShaderProgram, GL_FRAGMENT_SHADER, name);
  if (location == -1)
    std::cout<<"Could not bind attribute "<<name<<"\n";
  return location;
}



void GlShader::UniformSubroutinesuivF(const GLuint *location)
{

	glUniformSubroutinesuiv( GL_FRAGMENT_SHADER, 1, location);

}



//-------------------------------------------------------------------------
//-------------------------------------------------------------------------













