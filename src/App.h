#pragma once

#include <iostream>
#include <string>

#include "Tools.h"

namespace tsr
{
class App final
{
private:
    App();

public:
    ~App() = default;
    NOT_COPYABLE(App);
    static App& getInstance();

    void run();
};
}