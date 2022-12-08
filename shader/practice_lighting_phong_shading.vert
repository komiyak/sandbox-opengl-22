#version 150 core

in vec3 position;
in vec3 normal;

out vec3 FragmentPosition;
out vec3 Normal;

uniform mat4 projection_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

void main() {
    FragmentPosition = vec3(model_mat * vec4(position, 1.0f));

    // 法線は平行移動しない
    // 注意点：この model 行列に、不均一なスケール値を含んでいた場合は、法線の向きが狂ってしまいます
    Normal = vec3(model_mat * vec4(normal, 0.0));

    gl_Position = projection_mat * view_mat * model_mat * vec4(position, 1.0);
}
