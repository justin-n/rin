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

        std::cout << std::endl;

        printUsage();

        delete argumentHandler;

        return 1;
    }

    RunTimeState *runTimeState = new RunTimeState(argumentHandler->getSearchString(),
                                                  argumentHandler->getFilenameToSearch(),
                                                  argumentHandler->getOptions(),
                                                  argumentHandler->getDirectoriesToIgnore(),
                                                  argumentHandler->getExtensionsToIgnore());

    delete argumentHandler;

    if (_isatty(_fileno(stdin))) {

        if (runTimeState->getOptions() & opts::search_single_file) {

            printMatchesInFile(runTimeState->getFilenameToSearch(), runTimeState);
        }
        else {

            enumerateAndSearchFiles(".", runTimeState, 0);
        }
    }
    else {

        searchStdout(runTimeState);
    }

    delete runTimeState;

    return 0;
}

void printUsage() {
    std::cout << "Finds exact strings (not patterns) in the lines of files." << std::endl;
    std::cout << std::endl;
    std::cout << "If a filename to search is not provided, files will be searched" << std::endl;
    std::cout << "recursively from the current working directory." << std::endl;
    std::cout << std::endl;
    std::cout << "    rin [-ed=[dirs]] searchString [FILE]" << std::endl;
    std::cout << std::endl;
    std::cout << "      -ed=[dirs]" << std::endl;
    std::cout << "          Ignore a comma-separated list of directory names. If" << std::endl;
    std::cout << "          this argument is repeated, the values of each argument" << std::endl;
    std::cout << "          will be combined." << std::endl;
    std::cout << std::endl;
    std::cout << "stdout can be searched by using rin through a pipe:" << std::endl;
    std::cout << std::endl;
    std::cout << "    <command> | rin [searchString]" << std::endl;
    std::cout << std::endl;
}
