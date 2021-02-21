#include "pipeoperations.h"

#include <iostream>
#include <string>
#include <vector>

#include "runtimestate.h"
#include "matchprinter.h"
#include "options.h"

void printStringMatchesInStdout(RuntimeState *runtimeState) {

    std::string inputLine;

    size_t searchStringLen = runtimeState->getSearchStringLen();

    while (getline(std::cin, inputLine)) {

        std::vector<size_t> matchedPositions = getMatchedPositions(inputLine, runtimeState);

        if (matchedPositions.size() > 0) {

            printMatchesInLine(searchStringLen, matchedPositions, inputLine);

            std::cout << std::endl;
        }
    }
}

void printRegexMatchesInStdout(RuntimeState *runtimeState) {

    std::string inputLine;

    while (getline(std::cin, inputLine)) {

        findAndPrintRegexMatchesInLine(inputLine, runtimeState);
    }
}

void printNonStringMatchesInStdout(RuntimeState *runtimeState) {

    std::string inputLine;

    size_t searchStringLen = runtimeState->getSearchStringLen();

    while (getline(std::cin, inputLine)) {

        std::vector<size_t> matchedPositions = getMatchedPositions(inputLine, runtimeState);

        if (matchedPositions.size() == 0) {

            std::cout << inputLine << std::endl;
        }
    }
}
