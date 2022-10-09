#include "App.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
    tsr::App& rApp = tsr::App::getInstance();

    try
    {
        rApp.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}