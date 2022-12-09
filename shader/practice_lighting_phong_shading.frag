#version 150 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 FragmentPosition;
in vec3 Normal;

out vec4 outColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

uniform Material material;

void main()
{
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = lightColor * material.ambient;

    // Diffuse
    vec3 lightDirection = normalize(lightPosition - FragmentPosition);
    vec3 diffuse = lightColor * (max(dot(Normal, lightDirection), 0.0) * material.diffuse);

    // Specular
    vec3 viewDirection = normalize(viewPosition - FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, Normal);
    float specular_value = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = lightColor * (specular_value * material.specular);

    outColor = vec4((ambient + diffuse + specular) * objectColor, 1.0);
}
