#ifndef SANDBOX_OPENGL_22_LEARNOPENGL_LIGHTING_MULTIPLE_LIGHTS_H_
#define SANDBOX_OPENGL_22_LEARNOPENGL_LIGHTING_MULTIPLE_LIGHTS_H_

#include <glm/glm.hpp>

#include "../opengl_glfw.h"
#include "shader_uniform.h"

class LearnopenglLightingMultipleLights : public ShaderUniform {

private:
    GLint uniform_view_position_{-1};
    GLint uniform_material_diffuse_{-1};
    GLint uniform_material_specular_{-1};
    GLint uniform_material_shininess_{-1};
    GLint uniform_directional_light_direction_{-1};
    GLint uniform_directional_light_ambient_{-1};
    GLint uniform_directional_light_diffuse_{-1};
    GLint uniform_directional_light_specular_{-1};
};


#endif //SANDBOX_OPENGL_22_LEARNOPENGL_LIGHTING_MULTIPLE_LIGHTS_H_
