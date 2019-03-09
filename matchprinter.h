#include <vector>
#include <string>

#include "casemode.h"

#ifndef MatchPrinter_H
#define MatchPrinter_H

std::vector<size_t> getMatchedPositions(std::string searchString, size_t searchStringLen, std::string line, CaseMode caseMode);
void printMatchesInFile(std::string searchString, std::string fileName, CaseMode caseMode);
void printMatchesInLine(int lineNumber, size_t searchStringLen, std::vector<size_t> matchedPositions, std::string line);

#endif
