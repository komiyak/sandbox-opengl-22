#ifndef SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_MULTIPLE_LIGHTS_SCENE_H_
#define SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_MULTIPLE_LIGHTS_SCENE_H_

#include "../opengl_glfw.h"
#include "../application/scene.h"

// LearnOpenGL.com の lighting / Multiple lights の学習用のシーン
// https://learnopengl.com/Lighting/Multiple-lights
class LearnOpenGlLightingMultipleLightsScene : public Scene {
public:
    void OnStart() override;

    void OnFrame() override;

    void OnDestroy() override;

    void OnKey(int glfw_key, int glfw_action) override;

    static Scene *CreateFactory() {
        return new LearnOpenGlLightingMultipleLightsScene();
    }
};


#endif //SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_MULTIPLE_LIGHTS_SCENE_H_
