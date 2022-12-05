#ifndef SANDBOX_OPENGL_22_LIGHTING_EXAMPLE_ACTIVITY_H_
#define SANDBOX_OPENGL_22_LIGHTING_EXAMPLE_ACTIVITY_H_

#include "application.h"

class LightingExampleActivity : public Application::Activity {
public:
    void OnFrame() override;

    void OnStart() override;

    void OnDestroy() override;

    void OnKey(int glfw_key, int glfw_action) override;

    static Application::Activity *CreateActivityFactory() {
        return new LightingExampleActivity();
    }
};


#endif //SANDBOX_OPENGL_22_LIGHTING_EXAMPLE_ACTIVITY_H_
