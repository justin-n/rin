#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "matchprinter.h"
#include "filehandler.h"

void printUsage();

int main(int argc, char** argv) {

    if (argc == 1) {
        std::cout << "Please provide a string to search." << std::endl;
        std::cout << std::endl;
        printUsage();
        return 0;
    }

    std::string searchString;

    std::string fileName;

    if (argc >= 2) {
        searchString = argv[1];
    }

    if (argc == 3) {
        fileName = argv[2];
    }

    std::vector<std::string> extensionsToIgnore;
    extensionsToIgnore.push_back(".exe");
    extensionsToIgnore.push_back(".dll");

    // printMatchesInFile(searchString, fileName);

    enumerateAndSearchFiles(".", searchString, extensionsToIgnore, 0);

    return 0;
}

void printUsage() {
    std::cout << "Finds exact strings (not patterns) in the lines of files." << std::endl;
    std::cout << std::endl;
    std::cout << "test [searchString] [fileName]" << std::endl;
    std::cout << std::endl;
    std::cout << "If [fileName] is not provided, files will be searched recursively from the current" << std::endl;
    std::cout << "working directory." << std::endl;
    std::cout << std::endl;
}

