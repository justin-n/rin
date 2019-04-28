#ifndef FileHandler_H
#define FileHandler_H

#include <string>
#include <vector>

#include "options.h"

void enumerateAndSearchFiles(
        std::string directory, 
        std::string searchString,
        std::vector<std::string> directoriesToIgnore,
        std::vector<std::string> extensionsToIgnore,
        int depthLevel,
        opts::option_fields options
);
bool ignoreFileByExtension(std::string extension, std::vector<std::string> extensionsToIgnore);
bool ignoreDirectory(std::string fileName, std::vector<std::string> directoriesToIgnore);

#endif
