#include "matchprinter.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include "cmdcolors.h"
#include "options.h"

void printMatchesInFile(std::string fileName, RunTimeState *runTimeState);

void printNumberedMatchesInLine(size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line, int lineNumber);

void printMatchesInLine(size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line);

std::vector<size_t> getMatchedPositions(std::string line, RunTimeState *runTimeState);

void printMatchedString(std::string line, size_t printPos, size_t searchStringLen);

void printFileNameAndOrLineContainingMatch(
        std::vector<size_t> matchedPositions,
        bool &matchFound,
        std::string fileName,
        int searchStringLen,
        std::string line,
        int lineNumber);

std::string twoSpaceIndent = "  ";

void printMatchesInFile(std::string fileName, RunTimeState *runTimeState) {

    size_t searchStringLen = runTimeState->getSearchStringLen();

    std::ifstream infile(fileName);

    if (infile) {

        std::string line;

        int lineNumber = 1;

        bool matchFound = false;

        while (std::getline(infile, line)) {

            size_t substrPos;
            size_t nextSearchStartIndex = 0;

            std::vector<size_t> matchedPositions = getMatchedPositions(line, runTimeState);

            printFileNameAndOrLineContainingMatch(
                matchedPositions, matchFound, fileName, searchStringLen, line, lineNumber);

            lineNumber++;

        }

        if (matchFound) {

            std::cout << std::endl;
        }

    }
    else {

        std::cout << "There was a problem opening the file: " << fileName << std::endl;
    }

}

void printNumberedMatchesInLine(
        size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line, int lineNumber) {

    if (matchedPositions.size() <= 0) {

        std::cerr << "[WARNING]: matchedPositions vector is 0 or less in printNumberedMatchesInLine call." << std::endl;

        return;

    }

    std::cout << twoSpaceIndent << lineNumber << ": ";

    printMatchesInLine(searchStringLen, matchedPositions, line);
}

void printMatchesInLine(size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line) {

    if (matchedPositions.size() <= 0) {

        std::cerr << "[WARNING]: matchedPositions vector is 0 or less in printMatchesInLine call." << std::endl;

        return;

    }

    size_t printPos = 0;

    int machedPosIndex = 0;

    while (printPos < line.length()) {

        if (matchedPositions[machedPosIndex] == printPos) {

            machedPosIndex++;

            printMatchedString(line, printPos, searchStringLen);

            printPos += searchStringLen;
        }
        else if (printPos < matchedPositions[machedPosIndex]) {

            std::string matchlessSubstr = line.substr(printPos, (matchedPositions[machedPosIndex] - printPos));

            std::cout << matchlessSubstr;

            printPos += matchlessSubstr.length();
        }
        else {

            std::cout << line.substr(printPos);

            printPos += line.substr(printPos).length();
        }
    }
}

std::vector<size_t> getMatchedPositions(std::string line, RunTimeState *runTimeState) {

    size_t substrPos;
    size_t nextSearchStartIndex = 0;

    std::string searchString = runTimeState->getSearchString();
    size_t searchStringLen = runTimeState->getSearchStringLen();

    std::vector<size_t> matchedPositions;

    if (runTimeState->getOptions() & opts::ignore_case) {

        std::transform(line.begin(), line.end(), line.begin(), ::tolower);

        std::transform(searchString.begin(), searchString.end(), searchString.begin(), ::tolower);
    } 

    while ((substrPos = line.find(searchString, nextSearchStartIndex)) != std::string::npos) {

        nextSearchStartIndex = (substrPos + searchStringLen);

        matchedPositions.push_back(substrPos);
    }

    return matchedPositions;

}

void printFileNameAndOrLineContainingMatch(
        std::vector<size_t> matchedPositions,
        bool &matchFound,
        std::string fileName,
        int searchStringLen,
        std::string line,
        int lineNumber) {

    if (matchedPositions.size() > 0) {

        if (!matchFound) {

            std::cout << fileName << std::endl;

            matchFound = true;
        }

        printNumberedMatchesInLine(searchStringLen, matchedPositions, line, lineNumber);

        std::cout << std::endl;
    }
}

void printMatchedString(std::string line, size_t printPos, size_t searchStringLen) {

    setTextToRed();

    std::cout << line.substr(printPos, searchStringLen);

    setTextToUserColor();
}
