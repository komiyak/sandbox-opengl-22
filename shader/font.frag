#version 150 core

in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;
uniform vec3 color;

void main() {
    // Discarding fragments
    vec4 textureColor = texture(tex, Texcoord);
    if (textureColor.a < 0.1)
    discard;
    outColor = vec4(color, 1.0);
}
