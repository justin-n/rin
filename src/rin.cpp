#include <iostream>
#include <string>
#include <io.h>

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

    RuntimeState *runtimeState = new RuntimeState(argumentHandler->getSearchString(),
                                                  argumentHandler->getFilenameToSearch(),
                                                  argumentHandler->getOptions(),
                                                  argumentHandler->getDirectoriesToIgnore(),
                                                  argumentHandler->getExtensionsToIgnore());

    delete argumentHandler;

    try {
        runtimeState->init();
    }
    catch (const std::regex_error &e) {

        std::cout << "Regex error: " << e.what() << std::endl;

        std::cout << std::endl;

        delete runtimeState;

        return 1;
    }

    if (_isatty(_fileno(stdin))) {

        if (runtimeState->getOptions() & opts::search_single_file) {

            printMatchesInFile(runtimeState->getFilenameToSearch(), runtimeState);
        }
        else {

            enumerateAndSearchFiles(".", runtimeState, 0);
        }
    }
    else {

        searchStdout(runtimeState);
    }

    delete runtimeState;

    return 0;
}

void printUsage() {
    std::cout << "Finds strings or patterns in the lines of files." << std::endl;
    std::cout << std::endl;
    std::cout << "If a filename to search is not provided, files will be searched" << std::endl;
    std::cout << "recursively from the current working directory." << std::endl;
    std::cout << std::endl;
    std::cout << "    rin [-ed=[dirs]] [-rgx] searchString [FILE]" << std::endl;
    std::cout << std::endl;
    std::cout << "      -ed=[dirs]" << std::endl;
    std::cout << "          Ignore a comma-separated list of directory names. If" << std::endl;
    std::cout << "          this argument is repeated, the values of each argument" << std::endl;
    std::cout << "          will be combined." << std::endl;
    std::cout << std::endl;
    std::cout << "      -rgx" << std::endl;
    std::cout << "          searchString will be treated as a regex string. If this" << std::endl;
    std::cout << "          argument is not included, searchString will be treated as" << std::endl;
    std::cout << "          a literal string." << std::endl;
    std::cout << std::endl;
    std::cout << "stdout can be searched by using rin through a pipe:" << std::endl;
    std::cout << std::endl;
    std::cout << "    <command> | rin [searchString]" << std::endl;
    std::cout << std::endl;
}
