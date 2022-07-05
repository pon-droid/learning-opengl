 #define STB_IMAGE_IMPLEMENTATION
 #include "stb_image.h"
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

unsigned int gen_texture(const std::string& filename){
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int w, h, channels;

  unsigned char *img = stbi_load(filename.c_str(), &w, &h, &channels, 0);

  if (img){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "IMAGE COULD NOT BE LOADED\n";
    return 1;
  }

  stbi_image_free(img);

  return texture;
}

unsigned int gen_texture(const std::string& filename, const std::string& png){
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int w, h, channels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *img = stbi_load(filename.c_str(), &w, &h, &channels, 0);

  if (img){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "IMAGE COULD NOT BE LOADED\n";
    return 1;
  }

  stbi_image_free(img);

  return texture;
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

  Shader shader("vertex_shader.src","frag_shader.src");


  

  
  float vertices[] = {      //Vertices   //Colours           //Textures
                     -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 
		     -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		      0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
		      0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   1.0f, 1.0f
   };



  unsigned int indices[] = {  
    0, 1, 2, // first triangle
    2, 3, 1  // second triangle
  };
  
  /*
   float vertices[] = {      //Vertices   //Colours           //Textures
                      0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f,1.0f, 
		      0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		      -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		      -0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f
   };
  */

 

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  

  //float offset = 0.0f;

  auto clouds = gen_texture("duck.jpeg");
  auto troll  = gen_texture("troll.png", "png");

  shader.use();
  shader.set_int("clouds", 0);
  shader.set_int("troll", 1);
  
  
  while (!glfwWindowShouldClose(window)) {
    //offset -= 0.001;
    esc_close(window);

    glClearColor(0.8f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, clouds);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, troll);
    

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
