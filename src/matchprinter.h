#ifndef MatchPrinter_H
#define MatchPrinter_H

#include <vector>
#include <string>

#include "runtimestate.h"
#include "options.h"

std::vector<size_t> getMatchedPositions(std::string line, RuntimeState *runtimeState);

void printMatchesInFile(std::string fileName, RuntimeState *runtimeState);

void printMatchesInLine(size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line);

#endif
