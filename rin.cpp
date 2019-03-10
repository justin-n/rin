#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "matchprinter.h"
#include "filehandler.h"
#include "options.h"

opts::option_fields getDefaultOptions();
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

    std::vector<std::string> extensionsToIgnore;
    extensionsToIgnore.push_back(".exe");
    extensionsToIgnore.push_back(".dll");

    // printMatchesInFile(searchString, fileName, options);

    enumerateAndSearchFiles(".", searchString, extensionsToIgnore, 0, options);

    return 0;
}

opts::option_fields getDefaultOptions() {

    opts::option_fields options = 0x0;

    options |= opts::recursive;
    options |= opts::ignore_case;
    options |= opts::print_line_numbers;

    return options;
}

void printUsage() {
    std::cout << "Finds exact strings (not patterns) in the lines of files." << std::endl;
    std::cout << std::endl;
    std::cout << "rin [searchString]" << std::endl;
    std::cout << std::endl;
    std::cout << "Files will be searched recursively from the current working directory." << std::endl;
    std::cout << std::endl;
}

