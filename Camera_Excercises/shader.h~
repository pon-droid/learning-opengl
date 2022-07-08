#pragma once

#include "glad.c"
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

struct Shader {
  unsigned int program; // shader program

  void shader_gen(const char *shader_src, const char *frag_src) {

    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &shader_src, NULL);

    glCompileShader(vertex_shader);

    int success;
    char info[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
      glGetShaderInfoLog(vertex_shader, 512, nullptr, info);
      std::cout << "Shader Compilation Failed\n" << info << "\n";
    }

    unsigned int frag_shader;
    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &frag_src, NULL);
    glCompileShader(frag_shader);

    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
      glGetShaderInfoLog(frag_shader, 512, nullptr, info);
      std::cout << "Fragment Compilation Failed\n" << info << "\n";
    }

    unsigned int shader;
    shader = glCreateProgram();

    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, frag_shader);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 512, nullptr, info);

      std::cout << "Shader Linking Failure\n" << info << "\n";
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);

    program = shader;
  }

  Shader() {
  };

  Shader(const std::string &vertex_dir, const std::string &frag_dir) {
    std::string vertex_src;
    std::string frag_src;

    std::ifstream vertex_file;
    std::ifstream frag_file;

    vertex_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    frag_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
      vertex_file.open(vertex_dir);
      frag_file.open(frag_dir);
      std::stringstream vertex_stream, frag_stream;

      vertex_stream << vertex_file.rdbuf();
      frag_stream << frag_file.rdbuf();

      vertex_file.close();
      frag_file.close();

      vertex_src = vertex_stream.str();
      frag_src = frag_stream.str();
    }

    catch (std::ifstream::failure e) {
      std::cout << "SHADER FILE COULD NOT BE READ\n";
    }

    shader_gen(vertex_src.c_str(), frag_src.c_str());
  }

  void use() { glUseProgram(program);  }

  void set_int(const std::string &var, int val) const {
    glUniform1i(glGetUniformLocation(program, var.c_str()), val);
  }

  void set_float(const std::string &var, float val) const {
    glUniform1f(glGetUniformLocation(program, var.c_str()), val);
  }

  void set_mat4(const std::string &var, const GLfloat *m) const {
    glUniformMatrix4fv(glGetUniformLocation(program, var.c_str()), 1, GL_FALSE, m);
  }
  
};
