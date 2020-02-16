#ifndef FileHandler_H
#define FileHandler_H

#include <string>
#include <vector>

#include "runtimestate.h"
#include "options.h"

void enumerateAndSearchFiles(std::string directory, RuntimeState *runtimeState, int depthLevel);

bool ignoreFileByExtension(std::string extension, std::vector<std::string> extensionsToIgnore);

bool ignoreDirectory(std::string fileName, std::vector<std::string> directoriesToIgnore);

bool includeFileByFileNameMatch(std::string fileName, std::regex fileNameRegex);

void printFileNameIfVerbose(RuntimeState *runtimeState, std::string directory, std::string fileName);

#endif
