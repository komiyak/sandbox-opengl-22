#version 150 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

// Spotlight
struct Light {
    vec3 position;
    vec3 direction;
    float cutoff;
    float outer_cutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
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
    vec3 lightDirection = normalize(light.position - FragmentPosition);
    vec3 diffuse = light.diffuse * (max(dot(Normal, lightDirection), 0.0) * texture(material.diffuse, Texcoord).rgb);

    // Specular
    vec3 viewDirection = normalize(viewPosition - FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, Normal);
    float specular_value = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * specular_value * vec3(texture(material.specular, Texcoord));

    // Light's attenuation
    float light_distance = length(light.position - FragmentPosition);
    float attenuation = 1.0 / (light.constant + light.linear * light_distance + light.quadratic * (light_distance * light_distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // spotlight (soft edge)
    float theta = dot(lightDirection, -light.direction);
    float epsilon = light.cutoff - light.outer_cutoff;
    float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    outColor = vec4(ambient + diffuse + specular, 1.0);
}
