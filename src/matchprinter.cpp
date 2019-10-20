#include "matchprinter.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <regex>

#include "cmdcolors.h"
#include "options.h"

void printMatchesInFile(std::string fileName, RuntimeState *runtimeState);
void findAndPrintRegexMatchesInLine(std::string line,
                                    std::string fileName,
                                    bool &matchFound,
                                    int lineNumber,
                                    RuntimeState *runtimeState);
void findAndPrintStringMatchesInLine(std::string line,
                                     std::string fileName,
                                     bool &matchFound,
                                     size_t searchStringLen,
                                     int lineNumber,
                                     RuntimeState *runtimeState);
void printNumberedMatchesInLine(size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line, int lineNumber);
void printMatchesInLine(size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line);
std::vector<size_t> getMatchedPositions(std::string line, RuntimeState *runtimeState);
void printFileNameIfFirstMatchInFile(std::string fileName, bool &matchFound);
void printMatchedString(std::string line, size_t printPos, size_t searchStringLen);
void printMatchedString(std::string matchedString);
void printFileNameAndOrLineContainingMatch(std::vector<size_t> matchedPositions,
                                           bool &matchFound,
                                           std::string fileName,
                                           int searchStringLen,
                                           std::string line,
                                           int lineNumber);

std::string twoSpaceIndent = "  ";
std::string colonSpace = ": ";

void printMatchesInFile(std::string fileName, RuntimeState *runtimeState) {

    size_t searchStringLen = runtimeState->getSearchStringLen();

    std::ifstream infile(fileName);

    if (infile) {

        std::string line;

        int lineNumber = 1;

        bool matchFound = false;

        while (std::getline(infile, line)) {

            if (runtimeState->getOptions() & opts::regex_search) {

                findAndPrintRegexMatchesInLine(line, fileName, matchFound, lineNumber, runtimeState);
            }
            else {

                findAndPrintStringMatchesInLine(line, fileName, matchFound, searchStringLen, lineNumber, runtimeState);
            }

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

void findAndPrintRegexMatchesInLine(std::string line,
                                    std::string fileName,
                                    bool &matchFound,
                                    int lineNumber,
                                    RuntimeState *runtimeState) {

    std::regex regex = runtimeState->getSearchRegex();

    std::sregex_iterator begin = std::sregex_iterator(line.begin(), line.end(), regex);

    std::sregex_iterator end;

    if (begin != end) {

        printFileNameIfFirstMatchInFile(fileName, matchFound);

        std::cout << twoSpaceIndent << lineNumber << colonSpace;

        int currentPositionInLine = 0;

        for (std::sregex_iterator match = begin; match != end; match++) {

            if (match->position() != currentPositionInLine) {

                std::cout << line.substr(currentPositionInLine, (match->position() - currentPositionInLine));

                currentPositionInLine = match->position();
            }

            printMatchedString(match->str());

            currentPositionInLine = (currentPositionInLine + match->length());
        }

        if (currentPositionInLine != line.size()) {

            std::cout << line.substr(currentPositionInLine) << std::endl;
        }
        else {

            std::cout << std::endl;
        }
    }
}

void findAndPrintStringMatchesInLine(std::string line,
                                     std::string fileName,
                                     bool &matchFound,
                                     size_t searchStringLen,
                                     int lineNumber,
                                     RuntimeState *runtimeState) {

    std::vector<size_t> matchedPositions = getMatchedPositions(line, runtimeState);

    printFileNameAndOrLineContainingMatch(
        matchedPositions, matchFound, fileName, searchStringLen, line, lineNumber);
}

void printNumberedMatchesInLine(
        size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line, int lineNumber) {

    if (matchedPositions.size() <= 0) {

        std::cerr << "[WARNING]: matchedPositions vector is 0 or less in printNumberedMatchesInLine call." << std::endl;

        return;

    }

    std::cout << twoSpaceIndent << lineNumber << colonSpace;

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

std::vector<size_t> getMatchedPositions(std::string line, RuntimeState *runtimeState) {

    size_t substrPos;
    size_t nextSearchStartIndex = 0;

    std::string searchString = runtimeState->getSearchString();
    size_t searchStringLen = runtimeState->getSearchStringLen();

    std::vector<size_t> matchedPositions;

    if (runtimeState->getOptions() & opts::ignore_case) {

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

        printFileNameIfFirstMatchInFile(fileName, matchFound);

        printNumberedMatchesInLine(searchStringLen, matchedPositions, line, lineNumber);

        std::cout << std::endl;
    }
}

void printFileNameIfFirstMatchInFile(std::string fileName, bool &matchFound) {

    if (!matchFound) {

        std::cout << fileName << std::endl;

        matchFound = true;
    }
}

void printMatchedString(std::string line, size_t printPos, size_t searchStringLen) {

    setTextToRed();

    std::cout << line.substr(printPos, searchStringLen);

    setTextToUserColor();
}

void printMatchedString(std::string matchedString) {

    setTextToRed();

    std::cout << matchedString;

    setTextToUserColor();
}
