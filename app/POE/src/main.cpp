#include <iostream>
#include <memory>

#include <niu2x/app.h>
#include "poe.h"

int main(int argc, const char** argv)
{
    // using ArgParser = niu2x::app::ArgParser;
    // ArgParser arg_parser("POE", "niu2x's POE");
    try {
        POE app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    } catch (const std::exception& e) {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

//! [fullsource]
