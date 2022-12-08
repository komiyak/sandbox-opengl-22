#version 150 core

in vec3 position;
in vec3 normal;

out vec3 LightingColor;

uniform mat4 projection_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

// For Gouraud shading variables
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

void main() {
    vec3 position_in_global = vec3(model_mat * vec4(position, 1.0));
    vec3 normal_in_global = vec3(model_mat * vec4(normal, 0.0));

    // To calculate for ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // To calculate for diffuse lighting
    vec3 lightDirection = normalize(lightPosition - position_in_global);
    vec3 diffuse = max(dot(lightDirection, normal_in_global), 0.0) * lightColor;

    // To calculate for specular lighting
    vec3 viewDirection = normalize(viewPosition - position_in_global);
    vec3 reflectDirection = reflect(-lightDirection, normal_in_global);
    float specular_value = pow(max(dot(reflectDirection, viewDirection), 0.0), 32);
    vec3 specular = 1 * specular_value * lightColor;

    LightingColor = vec3(ambient + diffuse + specular);
    gl_Position = projection_mat * view_mat * vec4(position_in_global, 1.0);
}
