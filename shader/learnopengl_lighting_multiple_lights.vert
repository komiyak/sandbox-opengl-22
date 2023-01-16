#version 150 core

in vec3 v_position;
in vec3 v_normal;
in vec2 v_texcoord;

out vec3 io_fragment_position;
out vec3 io_normal;
out vec2 io_texcoord;

uniform mat4 projection_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

void main() {
    io_fragment_position = vec3(model_mat * vec4(v_position, 1.0f));
    io_texcoord = v_texcoord;

    // 法線は平行移動しない
    // 注意点：この model 行列に、不均一なスケール値を含んでいた場合は、法線の向きが狂ってしまいます
    io_normal = vec3(model_mat * vec4(v_normal, 0.0));

    gl_Position = projection_mat * view_mat * model_mat * vec4(v_position, 1.0);
}
