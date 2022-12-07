#version 150 core

in vec3 FragmentPosition;
in vec3 Normal;

out vec4 outColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 lightDirection = normalize(lightPosition - FragmentPosition);
    vec3 diffuse = max(dot(Normal, lightDirection), 0.0) * lightColor;

    outColor = vec4((ambient + diffuse) * objectColor, 1.0);
}
