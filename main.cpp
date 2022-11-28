#include "application.h"
#include "main_application.h"

int main() {
    MainApplication main_application;
    Application application;
    application.Initialize(&main_application);
    application.RunLoop();
    application.Finalize();
    return 0;
}
