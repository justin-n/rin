#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <windows.h>

#include "argumenthandler.h"
#include "runtimestate.h"
#include "matchprinter.h"
#include "filehandler.h"
#include "pipeoperations.h"
#include "options.h"

void printUsage();

int main(int argc, char** argv) {

    ArgumentHandler *argumentHandler = new ArgumentHandler(argc, argv);

    try {
        argumentHandler->init();
    }
    catch (const std::exception &e) {

        std::cout << "Exception: " << e.what() << std::endl;

        delete argumentHandler;

        return 1;

    }

    RunTimeState *runTimeState = new RunTimeState(argumentHandler->getSearchString(),
                                                  argumentHandler->getOptions(),
                                                  argumentHandler->getDirectoriesToIgnore(),
                                                  argumentHandler->getExtensionsToIgnore());

    delete argumentHandler;

    if (_isatty(_fileno(stdin))) {

        enumerateAndSearchFiles(".", runTimeState, 0);

    } else {

        searchStdout(runTimeState);

    }

    delete runTimeState;

    return 0;
}

void printUsage() {
    std::cout << "Finds exact strings (not patterns) in the lines of files." << std::endl;
    std::cout << std::endl;
    std::cout << "Files will be searched recursively from the current working directory." << std::endl;
    std::cout << std::endl;
    std::cout << "    rin [-ed=[dirs]] [searchString]" << std::endl;
    std::cout << std::endl;
    std::cout << "      -ed=[dirs]" << std::endl;
    std::cout << "          Ignore a comma-separated list of directory names" << std::endl;
    std::cout << std::endl;
    std::cout << "stdout can be searched by using rin through a pipe:" << std::endl;
    std::cout << std::endl;
    std::cout << "    <command> | rin [searchString]" << std::endl;
    std::cout << std::endl;
}
