#include <memory>
#include <gl_app/application.h>
#include "scene/starting_scene.h"

// 最初に実行する Scene
static std::shared_ptr<gl_app::Scene> FirstSceneFactory() {
    return std::shared_ptr<gl_app::Scene>{new StartingScene()};
}

int main() {
    gl_app::Application application;
    application.CreateWindow(FirstSceneFactory);
    application.RunLoop();
    application.Destroy();
    return 0;
}
