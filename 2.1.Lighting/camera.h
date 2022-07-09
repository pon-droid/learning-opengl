 #pragma once
 #include <GLFW/glfw3.h>
 #include <glm/glm.hpp>
 #include <glm/gtc/matrix_transform.hpp>
 #include <glm/gtc/type_ptr.hpp>



struct Camera {
  glm::vec3 pos;
  glm::vec3 front;
  glm::vec3 up;

  glm::mat4 view;

  const float sensitivity_nd = 3.1f;
  const float move_speed_nd  = 3.5f;
  const float max_pitch      = 89.0f;

  float sensitivity;
  float move_speed;
  static float fov;
  


    
  
  
  Camera(glm::vec3 init_pos, glm::vec3 init_front, glm::vec3 init_up){
    pos = init_pos;
    front = init_front;
    up = init_up;

    yaw = pitch = last_y  = last_x = 0;
    sensitivity = move_speed = 0;
  }

  void update_delta(const float& delta_t) {
    sensitivity = sensitivity_nd * delta_t;
    move_speed  = move_speed_nd  * delta_t;
  }

  glm::mat4 return_view() const{
    return glm::lookAt(pos, pos + front, up);
  }

  float yaw, pitch;

  float last_x, last_y;
  
 void ctrl_direction(GLFWwindow *window){
    double pos_x, pos_y;

    glfwGetCursorPos(window, &pos_x, &pos_y);

    yaw += (pos_x - last_x) * sensitivity;

    pitch += (last_y - pos_y) * sensitivity;

    if(pitch > max_pitch){
      pitch = max_pitch;
    }

    if(pitch < -max_pitch){
      pitch = -max_pitch;
    }

    last_x = pos_x;
    last_y = pos_y;

    glm::vec3 dir;

    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));

    dir.y = sin(glm::radians(pitch));

    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(dir);

 }



  void ctrl_pos(GLFWwindow *window){
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
      pos += move_speed * front;
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
      pos -= move_speed * front;
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
      pos -= glm::normalize(glm::cross(front, up)) * move_speed;
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
      pos += glm::normalize(glm::cross(front, up)) * move_speed;
    }

  }


};

float Camera::fov = 90;
