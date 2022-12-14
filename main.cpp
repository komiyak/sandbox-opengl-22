#include "application/application.h"
#include "scene/starting_scene.h"

// 最初に実行する Scene
static Scene *FirstSceneFactory() {
    return new StartingScene();
}

int main() {
    Application application;
    application.Initialize(FirstSceneFactory);
    application.RunLoop();
    application.Finalize();
    return 0;
}
