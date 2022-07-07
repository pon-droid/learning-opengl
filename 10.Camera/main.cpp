 #include "ponland.c"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
 #include "stb_image.h"
 #include "shader.h"
// #include "glad.c"
 #include <GLFW/glfw3.h>
 #include <glm/glm.hpp>
 #include <glm/gtc/matrix_transform.hpp>
 #include <glm/gtc/type_ptr.hpp>
 #include <iostream>
 #include <math.h>
 #include <vector>
 #include <time.h>

 constexpr int WH = 720;
 constexpr int WW = 1280;

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
  //unsigned char *img = stbi_load(filename.c_str(), &w, &h, &channels, 0);
  //unsigned char *img = stbi_load_from_memory(PON_PIXEL_DATA, 542 * 383 * 3 + 1, &w, &h, &channels, 0);
  //if (img){
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, PON_WIDTH, PON_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, PON_PIXEL_DATA);
    glGenerateMipmap(GL_TEXTURE_2D);
    //} else {
    // std::cout << "IMAGE COULD NOT BE LOADED " << w << " " << h << " " << channels << " " << stbi_failure_reason() << "\n";
    //return 1;
    //}

    //stbi_image_free(img);

  return texture;
}

void set_ratio(GLFWwindow *window, float& mix){
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
    mix += 5;
  } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
    mix -= 5;
  }

}

void matrix_style(GLFWwindow *window, float& x, float& y, float& z){
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
    x -= 0.01;
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
    x += 0.01;
  }

  if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
    y += 0.01;
  }

  if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
    y -= 0.01;
  }

  if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
    x = y = 0;
    z = 1.0;
  }

  if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
    z += 0.01;
  }

  if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS){
    z -= 0.01;
  }

}

struct Cube {
  glm::vec3 pos;
  glm::mat4 model;
};
std::vector<glm::vec3> generate_cubes(size_t amount){
  std::vector<glm::vec3>cubes;

  auto random_pos = [](float f){
    float random = static_cast <float> (rand() / static_cast <float> (RAND_MAX/f));
    //std::cout << random << "\n";
    return random;
  };
    
  for(size_t i = 0; i < amount; i++){
    cubes.push_back(glm::vec3(random_pos(20), random_pos(20) ,random_pos(20)));
  }

  return cubes;
}

void ctrl_cam_pos(const float& delta_t,GLFWwindow *window, const glm::vec3& camera_front, const glm::vec3& camera_up, glm::vec3& camera_pos){

  const float cam_speed = 3.5f * delta_t;

  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    camera_pos += cam_speed * camera_front;
  }

  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    camera_pos -= cam_speed * camera_front;
  }

  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * cam_speed;
  }

  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * cam_speed;
  }

}

glm::vec3 ctrl_direction(float& lastx,float&lasty,float& yaw, float& pitch, GLFWwindow *window){
  double xpos, ypos;

  glfwGetCursorPos(window, &xpos, &ypos);

  float xoffset = xpos - lastx;
  float yoffset = lasty - ypos;

  lastx = xpos;
  lasty = ypos;

  const float sensitivity = 0.1f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;


  glm::vec3 dir;

  dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));

  dir.y = sin(glm::radians(pitch));

  dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
  return dir;
}

int main() {
  srand(time(NULL));
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

  std::string vertex_embed_src = {
    "#version 330 core \n"
"layout (location = 0) in vec3 aPos; \n"
"layout (location = 1) in vec2 aTexCoord; \n"
"//layout (location = 1) in vec3 Colour; \n"
"//layout (location = 2) in vec2 aTexCoord; \n"
" \n"
" \n"
"//out vec3 send_colour; \n"
"out vec2 Coord; \n"
" \n"
"//uniform float Offset; \n"
"uniform mat4 model; \n"
"uniform mat4 view; \n"
"uniform mat4 projection; \n"
" \n"
"void main(){ \n"
"// Multiplication is actually happening right to left \n"
"gl_Position = projection * view * model * vec4(aPos, 1.0f); \n"
" \n"
"//send_colour = Colour; \n"
"Coord = aTexCoord; \n"
" \n"
    "} \n"};

  std::string frag_embed_src = {
    "#version 330 core \n"
"out vec4 FragColor; \n"
"//in vec3 send_colour; \n"
"in vec2 Coord; \n"
" \n"
"uniform sampler2D clouds; \n"
"uniform sampler2D troll; \n"
" \n"
"uniform float mixer; \n"
" \n"
"void main(){ \n"
"//FragColor = texture(ourTexture, Coord) * vec4(send_colour, 1.0); \n"
"FragColor   = mix(texture(clouds, Coord), texture(troll, vec2(-Coord.x, Coord.y)), mixer); \n"
"} \n"
  };

  Shader shader;
  shader.shader_gen(vertex_embed_src.c_str(), frag_embed_src.c_str());

  //Cube
  /*
  float vertices[] = {
    //Vertices         //Textures
    -0.5f, 0.5f,-0.5f,  0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,  0.0f, 0.0f,
    -0.5f,-0.5f, 0.5f,  1.0f, 0.0f,
    -0.5f,-0.5f, -0.5f, 0.0f, 0.0f,

    //LEFT SIDE OF CUBE ^^^^
    
    //Right Side
    
    //Vertices          //Textures
    0.5f, 0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, 0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f, 0.5f,  1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f
  };

  unsigned int indices[] = {
    //Left Face Triangle 1
    0, 1, 2,
    //Left Face Triangle 2/Bottom Triag
    2, 3, 0,
    //Top Face Triangle 1
    0, 4, 5,
    //Top Face Triangle 2
    5, 1, 0,
    //Right Face Triangle 1
    4, 7, 5,
    //Right Face Triangle 2
    5, 6, 7,
    //Bottom Face Triangle 1
    3, 7, 6,
    //Bottom Face Triangle 2
    6, 2, 3,
    //Front Triangle 1
    0, 4, 7,
    //Front Triangle 2
    7, 3, 0,
    //Back Triangle 1
    0, 4, 7,
    //Back Triangle 2
    7, 3, 0
  };
 
  
  float vertices2[] = {      //Vertices   //Colours           //Textures
                     -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 
		     -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		      0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
		      0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   1.0f, 1.0f
   };
  */
  /*
   float vertices[] = {      //Vertices   //Colours           //Textures
                     -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 
		     -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, .55f,
		      0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   0.55f, 0.0f,
		      0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.55f, 0.55f
   };

  */
  /*
  unsigned int indices2[] = {  
    0, 1, 2, // first triangle
    2, 3, 1  // second triangle
  };
  */
  /*
   float vertices[] = {      //Vertices   //Colours           //Textures
                      0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f,1.0f, 
		      0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		      -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		      -0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f
   };
  */
      float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
 

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  
  //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
  //glEnableVertexAttribArray(2);
  

  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  

  //float offset = 0.0f;

  //auto clouds = gen_texture("duck.jpeg");
  //auto troll  = gen_texture("troll.png", "png");
  auto clouds = gen_texture("ponland.png", "png");
  auto troll = clouds;
  shader.use();
  shader.set_int("clouds", 0);
  shader.set_int("troll", 1);
  
  float mix = 0;
  /*
  glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
  vec = trans * vec;
  */

  
  
  glm::mat4 model = glm::mat4(1.0f);
  //rotate along x-axis
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  
  glm::mat4 view = glm::mat4(1.0f);
  //translating the scene in reverse
  view = glm::translate(view, glm::vec3(0, 0, -3.0f));

  //fov of 45 degrees
  glm::mat4 project = glm::perspective(glm::radians(90.0f),
  static_cast <float> (WW) / static_cast <float> (WH), 0.1f, 100.0f);

  shader.use();

  shader.set_mat4("model", glm::value_ptr(model));
  shader.set_mat4("view", glm::value_ptr(view));
  shader.set_mat4("projection", glm::value_ptr(project));

  glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 20.0f);

  glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, 1.0f);
  glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0);

  const float radius = 10.0f;



  glEnable(GL_DEPTH_TEST);

  

  auto cubes = generate_cubes(20);


  float delta_t = 0.0f;
  float frame_t = 0.0f;

  float yaw = -90.0f;
  float pitch = 0.0f;

  float lastx = 0;
  float lasty = 0;

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  
  while (!glfwWindowShouldClose(window)) {
    float get_time = glfwGetTime();
    delta_t = get_time - frame_t;
    frame_t = get_time;

    camera_front = glm::normalize(ctrl_direction(lastx,lasty,yaw,pitch,window));
    //offset -= 0.001;
    esc_close(window);

    ctrl_cam_pos(delta_t,window, camera_front, camera_up, camera_pos);
    //set_ratio(window,mix);
    /*manual control
    matrix_style(window, x, y, z);



    shader.use();
    trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(x, y, z));
    */
    //trans = glm::scale(trans, glm::vec3(2, 2, 2));
    shader.use();
    //set_ratio(window, angle);
    /*
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model,  glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
    shader.set_mat4("model", glm::value_ptr(model));
    */
    
    glClearColor(0.082f, 0.28f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    /*
    float cam_x = static_cast <float> (sin(glfwGetTime() * radius));

    float cam_z = static_cast <float> (cos(glfwGetTime() * radius));

    glm::mat4 view;
    */
    
    view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);


    shader.use();
    shader.set_float("mixer", mix);
    shader.set_mat4("view", glm::value_ptr(view));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, clouds);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, troll);
    

    glBindVertexArray(VAO);

    for(const auto &i: cubes){
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, i);
      float angle = static_cast <float> (glfwGetTime() * glm::radians(50.0f));
      /* if(rand() % 10 == 0){
	angle = static_cast <float>(glfwGetTime()) * glm::radians(75.0f);
	} */
      model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
      shader.set_mat4("model", glm::value_ptr(model));
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //d::cout << "HOW! " << sizeof(indices) / sizeof(unsigned int) << "\n";
    //glDrawElements(GL_TRIANGLES, 36/6 * 3, GL_UNSIGNED_INT, 0);

    //std::cout << "HOW!\n";
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
