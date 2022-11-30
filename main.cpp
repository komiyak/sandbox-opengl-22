#include "application.h"
#include "main_activity.h"

// 最初に実行する Application activity
static Application::Activity *FirstApplicationActivityFactory() {
    return new MainActivity();
}

int main() {
    Application application;
    application.Initialize(FirstApplicationActivityFactory);
    application.RunLoop();
    application.Finalize();
    return 0;
}
