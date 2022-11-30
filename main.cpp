#include "application.h"
#include "basic_sample_activity.h"

// 最初に実行する Application activity
static Application::Activity *FirstApplicationActivityFactory() {
    return new BasicSampleActivity();
}

int main() {
    Application application;
    application.Initialize(FirstApplicationActivityFactory);
    application.RunLoop();
    application.Finalize();
    return 0;
}
