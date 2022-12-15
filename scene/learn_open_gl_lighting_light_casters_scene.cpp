#include "../opengl_glfw.h"
#include "learn_open_gl_lighting_light_casters_scene.h"

void LearnOpenGlLightingLightCastersScene::OnStart() {

}

void LearnOpenGlLightingLightCastersScene::OnFrame() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LearnOpenGlLightingLightCastersScene::OnDestroy() {

}

void LearnOpenGlLightingLightCastersScene::OnKey(int glfw_key, int glfw_action) {
    Scene::OnKey(glfw_key, glfw_action);

    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        should_destroy_ = true;
    }
}
