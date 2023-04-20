#include <gl_app/application.h>
#include "scene/starting_scene.h"

int main() {
    gl_app::Application application;
    application.CreateWindow(StartingScene::Factory);
    application.RunLoop();
    application.Destroy();
    return 0;
}
