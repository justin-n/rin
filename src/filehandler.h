#ifndef FileHandler_H
#define FileHandler_H

#include <string>
#include <vector>

#include "runtimestate.h"
#include "options.h"

void enumerateAndSearchFiles(std::string directory, RuntimeState *runtimeState, int depthLevel);

void handleDirectory(std::string fileName, std::vector<std::string> &subdirectories, RuntimeState *runtimeState);

void handleFile(std::string fileName, std::string directory, RuntimeState *runtimeState);

void handleSubdirectories(std::string directory,
                          std::vector<std::string> subdirectories,
                          int depthLevel,
                          RuntimeState *runtimeState);

void searchFilesInSubdirectories(std::vector<std::string> subdirectories,
                                 std::string directory,
                                 int depthLevel,
                                 RuntimeState *runtimeState);

bool ignoreFileByExtension(std::string extension, std::vector<std::string> extensionsToIgnore);

bool ignoreDirectory(std::string fileName, std::vector<std::string> directoriesToIgnore);

bool includeFileByFileNameMatch(std::string fileName, std::regex fileNameRegex);

void printMatchesInFileAndFileNameIfVerbose(std::string fileName, std::string directory, RuntimeState *runtimeState);

void printFileNameIfVerbose(RuntimeState *runtimeState, std::string directory, std::string fileName);

#endif
