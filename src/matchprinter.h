#ifndef MatchPrinter_H
#define MatchPrinter_H

#include <vector>
#include <string>

#include "runtimestate.h"
#include "options.h"

std::vector<size_t> getMatchedPositions(std::string line, RunTimeState *runtimestate);

void printMatchesInFile(std::string fileName, RunTimeState *runTimeState);

void printMatchesInLine(size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line);

void printNumberedMatchesInLine(size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line, int lineNumber);

#endif
