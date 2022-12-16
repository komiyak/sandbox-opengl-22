#version 150 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

// Directional light
struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragmentPosition;
in vec3 Normal;
in vec2 Texcoord;

out vec4 outColor;

uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

void main()
{
    // Ambient
    vec3 ambient = light.ambient * texture(material.diffuse, Texcoord).rgb;

    // Diffuse
    vec3 lightDirection = normalize(-light.direction);
    vec3 diffuse = light.diffuse * (max(dot(Normal, lightDirection), 0.0) * texture(material.diffuse, Texcoord).rgb);

    // Specular
    vec3 viewDirection = normalize(viewPosition - FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, Normal);
    float specular_value = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * specular_value * vec3(texture(material.specular, Texcoord));

    outColor = vec4(ambient + diffuse + specular, 1.0);
}
