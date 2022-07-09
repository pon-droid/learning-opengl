#include "shader.h"
#include "camera.h"

constexpr float WINDOW_WIDTH = 1920;
constexpr float WINDOW_HEIGHT = 1080;

int main(){
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "pretty lighting", nullptr, nullptr);

  if(window == nullptr){
    std::cout << "WINDOW CREATION FAILURE\n";
    glfwTerminate();

    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "GLAD INIT FAILURE\n";
    return -2;
  }



  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  
  auto resize_window = [](GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
  };

  glfwSetFramebufferSizeCallback(window, resize_window);

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

  
  unsigned int VBO, VAO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);


  unsigned int lightVAO;
  glGenVertexArrays(1, &lightVAO);

  glBindVertexArray(lightVAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  

  Shader shader("vertex_shader.glsl", "frag_shader.glsl");

  shader.use();
  shader.set_vec3("obj_colour", glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));

  shader.set_vec3("light_colour", glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
  
  
  Shader light_shader("vertex_shader.glsl", "light_frag_shader.glsl");

  

  Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0));

  glm::mat4 project = glm::perspective(glm::radians(90.0f), static_cast <float> (WINDOW_WIDTH) /
				       static_cast <float> (WINDOW_HEIGHT), 0.1f, 100.0f);

  project = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

  //CHANGE LATER IF NOT TESTING
  
  shader.use();

  shader.set_mat4("projection", glm::value_ptr(project));
  shader.set_mat4("view", glm::value_ptr(camera.return_view()));

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, (glm::vec3(0.0f,0.0f,0.0f)));
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  
  shader.set_mat4("model", glm::value_ptr(model));

  

  light_shader.use();
  light_shader.set_mat4("projection", glm::value_ptr(project));
  light_shader.set_mat4("view", glm::value_ptr(camera.return_view()));


  
  glm::mat4 light_model = glm::mat4(1.0f);
  light_model = glm::translate(light_model, glm::vec3(1.0f, 1.0f, 0.0f));
  light_model = glm::scale(light_model, glm::vec3(.2f));

  //light_model = glm::rotate(light_model, glm::radians(-55.0f), glm::vec3(0.0f, 1.0f, 0.0f));


  light_shader.set_mat4("model", glm::value_ptr(light_model));

  glEnable(GL_DEPTH_TEST);
  
  while(!glfwWindowShouldClose(window)){

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    light_shader.use();

    glBindVertexArray(lightVAO);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glfwSwapBuffers(window);
    glfwPollEvents();


  }

  glfwTerminate();
    

  


  return 0;

}
