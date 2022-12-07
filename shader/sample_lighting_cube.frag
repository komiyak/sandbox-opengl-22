#version 150 core

in vec3 FragmentPosition;
in vec3 Normal;

out vec4 outColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 lightDirection = normalize(lightPosition - FragmentPosition);
    vec3 diffuse = max(dot(Normal, lightDirection), 0.0) * lightColor;

    vec3 viewDirection = normalize(viewPosition - FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, Normal);
    float specular_value = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 specular = 0.5 * specular_value * lightColor;

    outColor = vec4((ambient + diffuse + specular) * objectColor, 1.0);
}
