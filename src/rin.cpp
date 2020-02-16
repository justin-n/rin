#include <iostream>
#include <string>
#include <io.h>
#include <regex>
#include <stdexcept>

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
                                                  argumentHandler->getFileNameToSearch(),
                                                  argumentHandler->getFileNameRegexString(),
                                                  argumentHandler->getMaxDepthString(),
                                                  argumentHandler->getOptions(),
                                                  argumentHandler->getDirectoriesToIgnore(),
                                                  argumentHandler->getExtensionsToIgnore());

    delete argumentHandler;

    try {
        runtimeState->init();
    }
    catch (const std::regex_error &e) {

        std::cout << "Regex error: " << e.what() << std::endl;

        delete runtimeState;

        return 1;
    }
    catch (const std::invalid_argument &e) {

        std::cout << "Invalid argument: " << e.what() << std::endl;

        delete runtimeState;

        return 1;
    }
    catch (const std::out_of_range &e) {

        std::cout << "Out of range exception: " << e.what() << std::endl;

        delete runtimeState;

        return 1;
    }

    if (_isatty(_fileno(stdin))) {

        if (runtimeState->getOptions() & opts::search_single_file) {

            printMatchesInFile(runtimeState->getFileNameToSearch(), runtimeState);
        }
        else {

            enumerateAndSearchFiles(".", runtimeState, 0);
        }
    }
    else {

        if (runtimeState->getOptions() & opts::regex_search) {

            printRegexMatchesInStdout(runtimeState);
        }
        else {

            printStringMatchesInStdout(runtimeState);
        }
    }

    delete runtimeState;

    return 0;
}

void printUsage() {
    std::cout << "Finds strings or patterns in the lines of files." << std::endl;
    std::cout << std::endl;
    std::cout << "If a file name to search is not provided, files will be searched" << std::endl;
    std::cout << "recursively from the current working directory." << std::endl;
    std::cout << std::endl;
    std::cout << "    rin [-ed=[dirs]] [-in=[PATTERN]] [-md=[depth]] [-rgx] searchString [FILE]" << std::endl;
    std::cout << std::endl;
    std::cout << "      -ed=[dirs]" << std::endl;
    std::cout << "          Ignore a comma-separated list of directory names. If" << std::endl;
    std::cout << "          this argument is repeated, the values of each argument" << std::endl;
    std::cout << "          will be combined." << std::endl;
    std::cout << std::endl;
    std::cout << "      -in=[PATTERN]" << std::endl;
    std::cout << "          Only search files which have a file name matching the" << std::endl;
    std::cout << "          PATTERN." << std::endl;
    std::cout << std::endl;
    std::cout << "      -md=[depth]" << std::endl;
    std::cout << "          Search directories recursively with a maximum depth of" << std::endl;
    std::cout << "          the depth provided. Depth is an integer value parsed by" << std::endl;
    std::cout << "          std::stoi. The current directory has a depth of 0. If a" << std::endl;
    std::cout << "          negative value is provided, only the current directory" << std::endl;
    std::cout << "          will be searched." << std::endl;
    std::cout << std::endl;
    std::cout << "      -rgx" << std::endl;
    std::cout << "          searchString will be treated as a regex string. If this" << std::endl;
    std::cout << "          argument is not included, searchString will be treated as" << std::endl;
    std::cout << "          a literal string." << std::endl;
    std::cout << std::endl;
    std::cout << "      -v" << std::endl;
    std::cout << "          Verbose output will be used. Currently, each file being" << std::endl;
    std::cout << "          searched will be printed. This can be useful for finding" << std::endl;
    std::cout << "          directories that could be ignored to reduce the time of" << std::endl;
    std::cout << "          long searches." << std::endl;
    std::cout << std::endl;
    std::cout << "stdout can be searched by using rin through a pipe:" << std::endl;
    std::cout << std::endl;
    std::cout << "    <command> | rin [-rgx] [searchString]" << std::endl;
    std::cout << std::endl;
}
