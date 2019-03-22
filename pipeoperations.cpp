#include <iostream>
#include <string>
#include <vector>

#include "matchprinter.h"
#include "options.h"

void searchStdout(std::string searchString, opts::option_fields options) {

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

