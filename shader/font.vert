#version 150 core

in vec2 position;
in vec2 texcoord;

out vec2 Texcoord;

uniform vec2 translation_vec;
uniform vec2 scaling_vec;
uniform vec2 texcoord_translation_vec;
uniform vec2 texcoord_scaling_vec;

void main() {
    Texcoord = vec2(
    texcoord.x * texcoord_scaling_vec.x + texcoord_translation_vec.x,
    texcoord.y * texcoord_scaling_vec.y + texcoord_translation_vec.y);

    gl_Position = vec4(
    position.x * scaling_vec.x + translation_vec.x,
    position.y * scaling_vec.y + translation_vec.y,
    0.0,
    1.0);
}
