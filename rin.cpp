#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <windows.h>

#include "matchprinter.h"
#include "filehandler.h"
#include "pipeoperations.h"
#include "options.h"

opts::option_fields getDefaultOptions();
std::vector<std::string> getExtensionsToIgnore();
std::vector<std::string> convertCStringArrayToStringVector(char** arr, int arrLength);
std::vector<std::string> getStringVectorFromStringWithDelimiter(std::string str, std::string delim);
void printUsage();

int main(int argc, char** argv) {

    if (argc == 1) {
        std::cout << "Please provide at least a string to search." << std::endl;
        std::cout << std::endl;
        printUsage();
        return 1;
    }

    std::vector<std::string> directoriesToIgnore;

    std::vector<std::string> argvStringVector = convertCStringArrayToStringVector(argv, argc);

    if (argvStringVector.size() == 3) {

        if (argvStringVector[1].substr(0, 4) == "-ed=") {

            std::string directoryString = argvStringVector[1].substr(4, argvStringVector[1].size() - 1);

            directoriesToIgnore = getStringVectorFromStringWithDelimiter(directoryString, ",");
        }
        else {
            std::cout << "Invalid argument." << std::endl;
            printUsage();
            return 1;
        }
    }

    if (argc > 3) {
        std::cout << "Too many arguments provided." << std::endl;
        std::cout << std::endl;
        printUsage();
        return 1;
    }

    std::string searchString = argv[argc - 1];

    opts::option_fields options = getDefaultOptions();

    std::string fileName;

    std::vector<std::string> extensionsToIgnore = getExtensionsToIgnore();

    if (_isatty(_fileno(stdin))) {

        enumerateAndSearchFiles(".", searchString, directoriesToIgnore, extensionsToIgnore, 0, options);

    } else {

        searchStdout(searchString, options);

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

std::vector<std::string> convertCStringArrayToStringVector(char** arr, int arrLength) {

    std::vector<std::string> stringVector;

    for (int i = 0; i < arrLength; i++) {

        stringVector.push_back(arr[i]);
    }

    return stringVector;
}

std::vector<std::string> getStringVectorFromStringWithDelimiter(std::string str, std::string delim) {

    std::vector<std::string> stringVector;

    size_t nextPos;

    bool lastMatchFound = false;

    while (!lastMatchFound) {

        if ((nextPos = str.find(delim)) == std::string::npos) {

            lastMatchFound = true;
        }

        stringVector.push_back(str.substr(0, nextPos));

        if (!lastMatchFound) {

            str = str.substr(nextPos + 1, str.length());
        }
    }

    return stringVector;
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

