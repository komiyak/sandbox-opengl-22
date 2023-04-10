#include <memory>
#include "application/application.h"
#include "scene/starting_scene.h"

// 最初に実行する Scene
static std::shared_ptr<Scene> FirstSceneFactory() {
    return std::shared_ptr<Scene>{new StartingScene()};
}

int main() {
    Application application;
    application.CreateWindow(FirstSceneFactory);
    application.RunLoop();
    application.Destroy();
    return 0;
}
