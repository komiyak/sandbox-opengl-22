#version 150 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragmentPosition;
in vec3 Normal;

out vec4 outColor;

uniform vec3 viewPosition;

uniform Material material;
uniform Light light;

void main()
{
    // Ambient
    vec3 ambient = light.ambient * material.ambient;

    // Diffuse
    vec3 lightDirection = normalize(light.position - FragmentPosition);
    vec3 diffuse = light.diffuse * (max(dot(Normal, lightDirection), 0.0) * material.diffuse);

    // Specular
    vec3 viewDirection = normalize(viewPosition - FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, Normal);
    float specular_value = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * (specular_value * material.specular);

    outColor = vec4(ambient + diffuse + specular, 1.0);
}
