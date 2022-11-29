#version 150 core

in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;

void main() {
    // Discarding fragments
    vec4 textureColor = texture(tex, Texcoord);
    if (textureColor.a < 0.1)
        discard;
    outColor = textureColor;
}
