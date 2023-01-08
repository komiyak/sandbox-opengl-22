#version 150 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

// Directional light
struct DirectionalLight {
    vec3 direction;// The direction of the light
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Point light
struct PointLight {
    vec3 position;

    float attenuation_constant;
    float attenuation_linear;
    float attenuation_quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Spotlight
struct Spotlight {
    vec3 position;
    vec3 direction;
    float cutoff;
    float outer_cutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float attenuation_constant;
    float attenuation_linear;
    float attenuation_quadratic;
};

in vec3 io_fragment_position;
in vec3 io_normal;
in vec2 io_texcoord;

out vec4 io_color;


#define NR_POINT_LIGHTS (4)

// Viewer (a camera) position.
uniform vec3 view_position;
// Render target's material.
uniform Material material;
// Directional light.
uniform DirectionalLight directional_light;
// Point lights.
uniform PointLight point_lights[NR_POINT_LIGHTS];
// Spotlight.
uniform Spotlight spotlight;


// prototypes
vec3 CalculateDirectionalLight(DirectionalLight directional_light_, Material material_, vec2 texcoord_, vec3 normal_, vec3 view_direction_);
vec3 CalculatePointLight(PointLight point_light_, Material material_, vec2 texcoord_, vec3 normal_, vec3 fragment_position_, vec3 view_direction_);
vec3 CalculateSpotlight(Spotlight spotlight_, Material material_, vec2 texcoord_, vec3 normal_, vec3 fragment_position_, vec3 view_direction_);


void main()
{
    // Define an output color value
    vec3 color_ = vec3(0.0);

    vec3 view_direction_ = normalize(view_position - io_fragment_position);

    // Add the directional light's contribution to the output
    color_ += CalculateDirectionalLight(directional_light, material, io_texcoord, io_normal, view_direction_);

    // Do the same for all point lights
    for (int i = 0; i < NR_POINT_LIGHTS; i++) {
        color_ += CalculatePointLight(point_lights[i], material, io_texcoord, io_normal, io_fragment_position, view_direction_);
    }

    // And add others lights as well (like spotlights)
    color_ += CalculateSpotlight(spotlight, material, io_texcoord, io_normal, io_fragment_position, view_direction_);

    io_color = vec4(color_, 0.0);
}

// Calculate a color contributed by the directional light.
// https://learnopengl.com/Lighting/Light-casters # Directional light
vec3 CalculateDirectionalLight(DirectionalLight directional_light_, Material material_, vec2 texcoord_, vec3 normal_, vec3 view_direction_)
{
    vec3 light_direction_ = normalize(-directional_light_.direction);

    // diffuse shading
    float diffuse_value_ = max(dot(normal_, light_direction_), 0.0);

    // specular shading
    vec3 reflection_ = reflect(-light_direction_, normal_);
    float specular_value_ = pow(max(dot(view_direction_, reflection_), 0.0), material_.shininess);

    // Combine results
    vec3 ambient_ = directional_light_.ambient * vec3(texture(material_.diffuse, texcoord_));
    vec3 diffuse_ = directional_light_.diffuse * diffuse_value_ * vec3(texture(material_.diffuse, texcoord_));
    vec3 specular_ = directional_light_.specular * specular_value_ * vec3(texture(material_.specular, texcoord_));

    return ambient_ + diffuse_ + specular_;
}

// Calculate a color contributed by the point light.
// https://learnopengl.com/Lighting/Light-casters # point light
vec3 CalculatePointLight(PointLight point_light_, Material material_, vec2 texcoord_, vec3 normal_, vec3 fragment_position_, vec3 view_direction_) {
    // Ambient
    vec3 ambient_ = point_light_.ambient * texture(material_.diffuse, texcoord_).rgb;

    // Diffuse
    vec3 light_direction_ = normalize(point_light_.position - fragment_position_);
    vec3 diffuse_ = point_light_.diffuse * (max(dot(normal_, light_direction_), 0.0) * texture(material_.diffuse, texcoord_).rgb);

    // Specular
    vec3 reflect_direction_ = reflect(-light_direction_, normal_);
    float specular_value_ = pow(max(dot(view_direction_, reflect_direction_), 0.0), material_.shininess);
    vec3 specular_ = point_light_.specular * specular_value_ * vec3(texture(material_.specular, texcoord_));

    // Light's attenuation
    float light_distance_ = length(point_light_.position - fragment_position_);
    float attenuation_ = 1.0 / (point_light_.attenuation_constant + point_light_.attenuation_linear * light_distance_ + point_light_.attenuation_quadratic * (light_distance_ * light_distance_));

    ambient_ *= attenuation_;
    diffuse_ *= attenuation_;
    specular_ *= attenuation_;

    return ambient_ + diffuse_ + specular_;
}

// Calculate a color contributed by the spotlight.
// https://learnopengl.com/Lighting/Light-casters # spotlight
vec3 CalculateSpotlight(Spotlight spotlight_, Material material_, vec2 texcoord_, vec3 normal_, vec3 fragment_position_, vec3 view_direction_) {
    // Ambient
    vec3 ambient_ = spotlight_.ambient * texture(material_.diffuse, texcoord_).rgb;

    // Diffuse
    vec3 light_direction_ = normalize(spotlight_.position - fragment_position_);
    vec3 diffuse_ = spotlight_.diffuse * (max(dot(normal_, light_direction_), 0.0) * texture(material_.diffuse, texcoord_).rgb);

    // Specular
    vec3 reflect_direction_ = reflect(-light_direction_, normal_);
    float specular_value_ = pow(max(dot(view_direction_, reflect_direction_), 0.0), material_.shininess);
    vec3 specular_ = spotlight_.specular * specular_value_ * vec3(texture(material_.specular, texcoord_));

    // Light's attenuation
    float light_distance_ = length(spotlight_.position - fragment_position_);
    float attenuation_ = 1.0 / (spotlight_.attenuation_constant + spotlight_.attenuation_linear * light_distance_ + spotlight_.attenuation_quadratic * (light_distance_ * light_distance_));

    ambient_ *= attenuation_;
    diffuse_ *= attenuation_;
    specular_ *= attenuation_;

    // spotlight (soft edge)
    float theta_ = dot(light_direction_, -spotlight_.direction);
    float epsilon_ = spotlight_.cutoff - spotlight_.outer_cutoff;
    float intensity_ = clamp((theta_ - spotlight_.outer_cutoff) / epsilon_, 0.0, 1.0);
    diffuse_ *= intensity_;
    specular_ *= intensity_;

    return ambient_ + diffuse_ + specular_;
}
