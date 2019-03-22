#ifndef FileHandler_H
#define FileHandler_H

#include <string>
#include <vector>

#include "options.h"

void enumerateAndSearchFiles(
        std::string directory, 
        std::string searchString,
        std::vector<std::string> extensionsToIgnore,
        int depthLevel,
        opts::option_fields options
);
bool ignoreFile(std::string extension, std::vector<std::string> extensionsToIgnore);
void printDepthLevel(int depthLevel);

#endif
