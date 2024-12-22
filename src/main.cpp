#include "app.h"
#include <windows.h>

int main(int argc, char** argv) {
    try {
        App* app = new App();
        app->run();
        delete app;
    } catch (const std::exception& e) {
        MessageBoxA(NULL, e.what(), "Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    return 0;
}
