#ifndef SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_LIGHT_CASTERS_SCENE_H_
#define SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_LIGHT_CASTERS_SCENE_H_

#include <glad/glad.h>

#include "../application/scene.h"

// LearnOpenGL.com の lighting / light casters の学習用のシーン
// https://learnopengl.com/Lighting/Light-casters
class LearnOpenGlLightingLightCastersScene : public Scene {
public:
    void OnStart() override;

    void OnFrame() override;

    void OnDestroy() override;

    void OnKey(int glfw_key, int glfw_action) override;

    static Scene *CreateFactory() {
        return new LearnOpenGlLightingLightCastersScene();
    }
};


#endif //SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_LIGHT_CASTERS_SCENE_H_
