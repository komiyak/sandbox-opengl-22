#include "application.h"
#include "main_application.h"

int main() {
    MainApplication application_implementation;
    Application application;
    application.Initialize(&application_implementation);
    application.RunLoop();
    application.Finalize();
    return 0;
}
