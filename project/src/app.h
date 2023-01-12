#pragma once

#include <iostream>
#include <string>

#include "tools.hpp"

class QGuiApplication;
class QQmlApplicationEngine;

namespace tsr
{
class App final
{
    NOT_COPYABLE(App);
    QGuiApplication* mpApp;
    QQmlApplicationEngine* mpEngine;

public:
    App(int argc, char* argv[]);
    ~App();

    void run();
    void qmlRegister();
};
}