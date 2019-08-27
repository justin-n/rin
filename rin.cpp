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

opts::option_fields getDefaultOptions();
std::vector<std::string> getExtensionsToIgnore();
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

    std::string searchString = argv[argc - 1];

    opts::option_fields options = getDefaultOptions();

    std::vector<std::string> extensionsToIgnore = getExtensionsToIgnore();

    RunTimeState *runTimeState = new RunTimeState(searchString,
                                                  options,
                                                  argumentHandler->getDirectoriesToIgnore(),
                                                  extensionsToIgnore);

    delete argumentHandler;

    if (_isatty(_fileno(stdin))) {

        enumerateAndSearchFiles(".", runTimeState, 0);

    } else {

        searchStdout(runTimeState);

    }

    delete runTimeState;

    return 0;
}

opts::option_fields getDefaultOptions() {

    opts::option_fields options = 0x0;

    options |= opts::recursive;
    options |= opts::ignore_case;
    options |= opts::print_line_numbers;

    return options;
}

std::vector<std::string> getExtensionsToIgnore() {

    std::vector<std::string> extensionsToIgnore;

    extensionsToIgnore.push_back(".exe");
    extensionsToIgnore.push_back(".dll");
    extensionsToIgnore.push_back(".class");
    extensionsToIgnore.push_back(".jar");
    extensionsToIgnore.push_back(".zip");
    extensionsToIgnore.push_back(".swc");

    return extensionsToIgnore;
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
