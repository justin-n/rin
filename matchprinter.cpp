#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include "matchprinter.h"
#include "cmdcolors.h"
#include "options.h"

std::string twoSpaceIndent = "  ";

void printMatchesInFile(std::string searchString, std::string fileName, opts::option_fields options) {

    size_t searchStringLen = searchString.length();
    
    std::ifstream infile(fileName);

    if (infile) {

        std::string line;

        int lineNumber = 1;

        bool matchFound = false;

        while (std::getline(infile, line)) {

            size_t substrPos;
            size_t nextSearchStartIndex = 0;

            std::vector<size_t> matchedPositions = getMatchedPositions(searchString, searchStringLen, line, options);
            
            if (matchedPositions.size() > 0) {

                if (!matchFound) {

                    std::cout << fileName << std::endl;

                    matchFound = true;

                }

                printMatchesInLine(lineNumber, searchStringLen, matchedPositions, line);

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

void printMatchesInLine(int lineNumber, size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line) {

    size_t printPos = 0;

    int machedPosIndex = 0;

    std::cout << twoSpaceIndent << lineNumber << ": ";

    while (printPos < line.length()) {

        if (matchedPositions[machedPosIndex] == printPos) {

            machedPosIndex++;

            setTextToRed();

            std::cout << line.substr(printPos, searchStringLen);

            setTextToUserColor();

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

    std::cout << std::endl;
   
}

std::vector<size_t> getMatchedPositions(
        std::string searchString,
        size_t searchStringLen,
        std::string line,
        opts::option_fields options) {

    size_t substrPos;
    size_t nextSearchStartIndex = 0;

    std::vector<size_t> matchedPositions;

    if (options & opts::ignore_case) {

        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        std::transform(searchString.begin(), searchString.end(), searchString.begin(), ::tolower);

    } 
    
    while ((substrPos = line.find(searchString, nextSearchStartIndex)) != std::string::npos) {

        nextSearchStartIndex = (substrPos + searchStringLen);

        matchedPositions.push_back(substrPos);
    }

    return matchedPositions;
}
