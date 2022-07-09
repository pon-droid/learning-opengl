#version 330 core
layout (location = 0) in vec3 POS;
layout (location = 1) in vec2 TEXTURE; //Not using this rn

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){

gl_Position = projection * view * model * vec4(POS, 1.0);

}
