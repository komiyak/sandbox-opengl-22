#version 150 core

in vec3 position;

uniform mat4 projection_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

void main() {
    gl_Position = projection_mat * view_mat * model_mat * vec4(position, 1.0);
}
