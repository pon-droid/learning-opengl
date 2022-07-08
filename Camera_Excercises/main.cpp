 #include "ponland.c"
 #define STB_IMAGE_IMPLEMENTATION
 #define STBI_FAILURE_USERMSG
 #include "stb_image.h"
 #include "shader.h"
 #include "camera.h"
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

void ctrl_zoom(GLFWwindow *window, double x_amount, double y_amount){
  
  Camera::fov -= y_amount * 2;


  if(Camera::fov > 90){
    Camera::fov = 90;
  }

  if(Camera::fov < 1.0){
    Camera::fov = 1.0;
  }

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

unsigned int gen_texture_from_memory(unsigned char* raw_buffer, int width, int height){
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, raw_buffer);
  glGenerateMipmap(GL_TEXTURE_2D);


  return texture;
}



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


  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  

  auto clouds = gen_texture_from_memory(PON_PIXEL_DATA, PON_WIDTH, PON_HEIGHT);
  auto troll = clouds;
  shader.use();
  shader.set_int("clouds", 0);
  shader.set_int("troll", 1);
  

  
  

  /*
  glm::mat4 view = glm::mat4(1.0f);
  //translating the scene in reverse
  view = glm::translate(view, glm::vec3(0, 0, -3.0f));
  */
  
  //fov of 90 degrees
  //glm::mat4 project = glm::perspective(glm::radians(90.0f),
  //static_cast <float> (WW) / static_cast <float> (WH), 0.1f, 100.0f);



  //  shader.set_mat4("projection", glm::value_ptr(project));




  glEnable(GL_DEPTH_TEST);

  Camera camera(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0));

  

  auto cubes = generate_cubes(20);



  float frame_t = 0.0f;



  
  
  
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetScrollCallback(window, ctrl_zoom);
  
  
  while (!glfwWindowShouldClose(window)) {


    
    float get_time = glfwGetTime();
    float delta_t = get_time - frame_t;
    frame_t = get_time;

    camera.update_delta(delta_t);

    camera.ctrl_pos(window);
    camera.ctrl_direction(window);

    glm::mat4 project = glm::perspective(glm::radians(Camera::fov),
					   static_cast <float> (WW) / static_cast <float> (WH), 0.1f, 100.0f);

    
    esc_close(window);

        

    shader.use();

    shader.set_float("mixer", 0);
    shader.set_mat4("view", glm::value_ptr(camera.return_view()));
    shader.set_mat4("projection", glm::value_ptr(project));
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, clouds);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, troll);
    

    glBindVertexArray(VAO);



    glClearColor(0.082f, 0.28f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(const auto &i: cubes){
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, i);
      float angle = static_cast <float> (glfwGetTime() * glm::radians(50.0f));

      model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
      shader.set_mat4("model", glm::value_ptr(model));
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glfwTerminate();
  return 0;
}
