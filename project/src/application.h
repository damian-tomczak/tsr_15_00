#pragma once

#include <iostream>
#include <string>

#include "Tools.h"

class QGuiApplication;
class QQmlApplicationEngine;

namespace tsr
{
class Application final
{
    NOT_COPYABLE(Application);
    QGuiApplication* app;
    QQmlApplicationEngine* engine;

public:
    Application(int argc, char* argv[]);
    ~Application();

    void run();
};
}