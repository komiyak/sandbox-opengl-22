#include "learn_open_gl_lighting_multiple_lights_scene.h"

void LearnOpenGlLightingMultipleLightsScene::OnStart() {

}

void LearnOpenGlLightingMultipleLightsScene::OnFrame() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LearnOpenGlLightingMultipleLightsScene::OnDestroy() {

}

void LearnOpenGlLightingMultipleLightsScene::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        SendToDestroy();
    }
}
