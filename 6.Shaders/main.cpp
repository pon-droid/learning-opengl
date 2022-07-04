 #include "shader.h"
// #include "glad.c"
 #include <GLFW/glfw3.h>
 #include <iostream>
 #include <math.h>

 constexpr int WH = 500;
 constexpr int WW = 500;

 void update_winsize(GLFWwindow *window, int width, int height) {
   glViewport(0, 0, width, height);
 }

 void esc_close(GLFWwindow *window) {
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
     glfwSetWindowShouldClose(window, true);
   }
 }

// unsigned int gen_shader() {

//   /*
//           unsigned int VBO;
//           glGenBuffers(1, &VBO);

//           glBindBuffer(GL_ARRAY_BUFFER, VBO);

//           glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
//      GL_STATIC_DRAW);
//   */
//   const char *shader_src = {"#version 330 core\n"
//                             "layout (location = 0) in vec3 aPos;\n"
//                             "void main()\n"
//                             "{\n"
//                             "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
//                             "}\0"};

//   unsigned int vertex_shader;
//   vertex_shader = glCreateShader(GL_VERTEX_SHADER);

//   glShaderSource(vertex_shader, 1, &shader_src, NULL);

//   glCompileShader(vertex_shader);

//   int success;
//   char info[512];
//   glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

//   if (!success) {
//     glGetShaderInfoLog(vertex_shader, 512, nullptr, info);
//     std::cout << "Shader Compilation Failed\n" << info << "\n";
//   }

//   const char *frag_src = {"#version 330 core\n"
//                           "out vec4 FragColor;\n"
//                           "void main(){\n"
//                           "FragColor = vec4(1.0, .5, .2, 1.0);\n"
//                           "}\0"};

//   unsigned int frag_shader;
//   frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
//   glShaderSource(frag_shader, 1, &frag_src, NULL);
//   glCompileShader(frag_shader);

//   glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);

//   if (!success) {
//     glGetShaderInfoLog(frag_shader, 512, nullptr, info);
//     std::cout << "Fragment Compilation Failed\n" << info << "\n";
//   }

//   unsigned int shader;
//   shader = glCreateProgram();

//   glAttachShader(shader, vertex_shader);
//   glAttachShader(shader, frag_shader);
//   glLinkProgram(shader);

//   glGetProgramiv(shader, GL_LINK_STATUS, &success);
//   if (!success) {
//     glGetProgramInfoLog(shader, 512, nullptr, info);

//     std::cout << "Shader Linking Failure\n" << info << "\n";
//   }

//   glDeleteShader(vertex_shader);
//   glDeleteShader(frag_shader);
//   /*
// unsigned int VAO;
// glGenVertexArrays(1, &VAO);

//   glBindBuffer(GL_ARRAY_BUFFER, VBO);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
// glEnableVertexAttribArray(0);

// glUseProgram(shader);




// glBindVertexArray(VAO);

// glDrawArrays(GL_TRIANGLES, 0, 3);

// */

//   return shader;
// }

unsigned int shader_gen(const char *shader_src, const char *frag_src) {
//   /*
//           unsigned int VBO;
//           glGenBuffers(1, &VBO);

//           glBindBuffer(GL_ARRAY_BUFFER, VBO);

//           glBufferDat
/*	  a(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
     GL_STATIC_DRAW);
  */

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
  /*
unsigned int VAO;
glGenVertexArrays(1, &VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

glUseProgram(shader);




glBindVertexArray(VAO);

glDrawArrays(GL_TRIANGLES, 0, 3);

*/

  return shader;
}

void gen_colour(auto shader){
  int colour_location = glGetUniformLocation(shader, "Colour");

  float t = glfwGetTime();
  float r = sin(t);
  float g = sin(t) + .5;
  float b = r/g;

  glUniform4f(colour_location, r, g, b, 1.0f);

}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(WW, WH, "gee ell", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Window creation failed\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "GLAD init failed\n";
    return -2;
  }

  glViewport(0, 0, WW, WH);
  glfwSetFramebufferSizeCallback(window, update_winsize);
/*
  std::string shader_src = {"#version 330 core\n"
                            "layout (location = 0) in vec3 aPos;\n"
                            "layout (location = 1) in vec3 Colour;\n"
                            "out vec3 send_colour;\n"
                            "void main()\n"
                            "{\n"
                            "gl_Position = vec4(aPos, 1.0);\n"
                            "send_colour = Colour;\n"
                            "}\0"};

  std::string frag_src = {"#version 330 core\n"
                          "out vec4 FragColor;\n"
                          "in vec3 send_colour;\n"
                          "void main(){\n"
                          "FragColor = vec4(send_colour, 1.0);\n"
                          "}\0"};

  auto shader = shader_gen(shader_src.c_str(), frag_src.c_str());
*/
  Shader shader("vertex_shader.src","frag_shader.src");
  /*
  float vertices[] = {0.5f, 0.5f, 0.0f,
                      0.0f, 0.0f, 0.0f,
                      0.5f, 0.0f, 0.0f,
                      1.0f, 0.0f, 0.0f, //R
		      0.0f, 0.0f, 1.0f, //G
		      0.0f, 1.0f, 0.0f  //B
		      };*/

  float vertices[] = {0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f, //R 
                      0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, //G
                      0.5f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f  //B
                      
		     
		      
		      
   };

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);

  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  

  //float offset = 0.0f;


  while (!glfwWindowShouldClose(window)) {
    //offset -= 0.001;
    esc_close(window);

    glClearColor(0.8f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //gen_colour(shader);

    //shader.set_float("Offset", offset);
    shader.use();
    //glUseProgram(shader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}