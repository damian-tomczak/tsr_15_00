#include "application.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
    try
    {
        tsr::Application application = tsr::Application(argc, argv);
        application.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}