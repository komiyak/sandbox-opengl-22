#include "application.h"
#include "application_implementation.h"

int main() {
    ApplicationImplementation application_implementation;
    Application application;
    application.Initialize(&application_implementation);
    application.RunLoop();
    application.Finalize();
    return 0;
}
