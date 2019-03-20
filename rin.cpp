#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <windows.h>

#include "matchprinter.h"
#include "filehandler.h"
#include "options.h"

opts::option_fields getDefaultOptions();
std::vector<std::string> getExtensionsToIgnore();
void printUsage();

int main(int argc, char** argv) {

    if (argc == 1) {
        std::cout << "Please provide at least a string to search." << std::endl;
        std::cout << std::endl;
        printUsage();
        return 0;
    }

    opts::option_fields options = getDefaultOptions();

    std::string searchString;

    std::string fileName;

    if (argc >= 2) {
        searchString = argv[1];
    }

    std::vector<std::string> extensionsToIgnore = getExtensionsToIgnore();

    if (_isatty(_fileno(stdin))) {

        enumerateAndSearchFiles(".", searchString, extensionsToIgnore, 0, options);

    } else {

        std::string inputLine;

        while (getline(std::cin, inputLine)) {

            size_t searchStringLen = searchString.length();

            std::vector<size_t> matchedPositions = getMatchedPositions(searchString, searchStringLen, inputLine, options);

            if (matchedPositions.size() > 0) {

                printMatchesInLine(searchStringLen, matchedPositions, inputLine);

                std::cout << std::endl;

            }

        }

    }

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
    std::cout << "rin [searchString]" << std::endl;
    std::cout << std::endl;
    std::cout << "Files will be searched recursively from the current working directory." << std::endl;
    std::cout << std::endl;
}

