#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <regex>
#include <windows.h>
#include <shlwapi.h>

#include "runtimestate.h"
#include "filehandler.h"
#include "matchprinter.h"
#include "options.h"

void enumerateAndSearchFiles(std::string directory, RuntimeState *runtimeState, int depthLevel) {

    WIN32_FIND_DATA wfd;

    HANDLE hFile = INVALID_HANDLE_VALUE;

    std::string allFilesInDirectory = (directory + "\\*");

    hFile = FindFirstFile(allFilesInDirectory.c_str(), &wfd);

    if (hFile != INVALID_HANDLE_VALUE) {

        std::vector<std::string> subDirectories;

        do {

            std::string fileName = wfd.cFileName;

            if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                
                if (!ignoreDirectory(fileName, runtimeState->getDirectoriesToIgnore())) {

                    subDirectories.push_back(fileName);
                }
            }
            else {

                std::string fileExtension = PathFindExtension(fileName.c_str());

                if (!ignoreFileByExtension(fileExtension, runtimeState->getExtensionsToIgnore())) {

                    if (runtimeState->getOptions() & opts::file_name_match) {

                        if (includeFileByFileNameMatch(fileName, runtimeState->getFileNameRegex())) {

                            printFileNameIfVerbose(runtimeState, directory, fileName);

                            printMatchesInFile( (directory + "\\" + fileName) , runtimeState);
                        }
                    }
                    else {

                        printFileNameIfVerbose(runtimeState, directory, fileName);

                        printMatchesInFile( (directory + "\\" + fileName) , runtimeState);
                    }
                }
            }

        } while (FindNextFile(hFile, &wfd));

        FindClose(hFile);

        if (!subDirectories.empty()) {

            depthLevel++;
            
            for (int i = 0; i < subDirectories.size(); i++) {

                enumerateAndSearchFiles( (directory +"\\"+ subDirectories[i]), runtimeState, depthLevel);
            }
        }
    }
}

bool ignoreFileByExtension(std::string extension, std::vector<std::string> extensionsToIgnore) {

    for (int i = 0; i < extensionsToIgnore.size(); i++) {

        if (extension.compare(extensionsToIgnore[i]) == 0) {

            return true;
        }
    }

    return false;
}

bool ignoreDirectory(std::string fileName, std::vector<std::string> directoriesToIgnore) {

    if ((fileName.compare(".")) == 0 || (fileName.compare("..")) == 0) {

        return true;
    }

    std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);

    if (std::find(directoriesToIgnore.begin(), directoriesToIgnore.end(), fileName) != directoriesToIgnore.end()) {

        return true;
    }

    return false;
}

bool includeFileByFileNameMatch(std::string fileName, std::regex fileNameRegex) {

    if (std::regex_match(fileName, fileNameRegex)) {

        return true;
    }
    else {

        return false;
    }
}

void printFileNameIfVerbose(RuntimeState *runtimeState, std::string directory, std::string fileName) {

    if (runtimeState->getOptions() & opts::verbose) {

        std::cout << (directory + "\\" + fileName) << std::endl;
    }
}
