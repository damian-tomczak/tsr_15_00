#include "Application.h"

namespace tsr
{
App::App()
{

}

App::~App()
{

}

void App::run()
{
    std::cout << "Welcome " PROJECT_NAME " version: " PROJECT_VERSION "\n";
}
}