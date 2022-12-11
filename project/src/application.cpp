#include "App.h"

namespace tsr
{
App::App()
{

}

void App::run()
{
    std::cout << "Welcome " PROJECT_NAME " version: " PROJECT_VERSION "\n";
}

App& App::getInstance()
{
    static App instance;
    return instance;
}
}