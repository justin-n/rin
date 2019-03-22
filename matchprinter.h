#ifndef MatchPrinter_H
#define MatchPrinter_H

#include <vector>
#include <string>

#include "options.h"

std::vector<size_t> getMatchedPositions(
    std::string searchString,
    size_t searchStringLen,
    std::string line,
    opts::option_fields options
);
void printMatchesInFile(std::string searchString, std::string fileName, opts::option_fields options);
void printMatchesInLine(size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line);
void printNumberedMatchesInLine(size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line, int lineNumber);

#endif
