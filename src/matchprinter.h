#ifndef MatchPrinter_H
#define MatchPrinter_H

#include <vector>
#include <string>

#include "runtimestate.h"
#include "options.h"

std::vector<size_t> getMatchedPositions(std::string line, RuntimeState *runtimeState);

void printMatchesInFile(std::string fileName, RuntimeState *runtimeState);

void printMatchesInLine(size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line);

void findAndPrintRegexMatchesInLine(std::string line,
                                    std::string fileName,
                                    bool &matchFound,
                                    int lineNumber,
                                    RuntimeState *runtimeState);

void findAndPrintRegexMatchesInLine(std::string line, RuntimeState *runtimeState);

void findAndPrintStringMatchesInLine(std::string line,
                                     std::string fileName,
                                     bool &matchFound,
                                     size_t searchStringLen,
                                     int lineNumber,
                                     RuntimeState *runtimeState);

void printNumberedMatchesInLine(size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line, int lineNumber);

void printFileNameIfFirstMatchInFile(std::string fileName, bool &matchFound);

void printMatchedString(std::string line, size_t printPos, size_t searchStringLen);

void printMatchedString(std::string matchedString);

void printFileNameAndOrLineContainingMatch(std::vector<size_t> matchedPositions,
                                           bool &matchFound,
                                           std::string fileName,
                                           int searchStringLen,
                                           std::string line,
                                           int lineNumber);

#endif
