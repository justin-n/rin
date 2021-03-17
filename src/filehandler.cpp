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

        std::vector<std::string> subdirectories;

        do {

            std::string fileName = wfd.cFileName;

            if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

                handleDirectory(fileName, subdirectories, runtimeState);
            }
            else {

                handleFile(fileName, directory, runtimeState);
            }

        } while (FindNextFile(hFile, &wfd));

        FindClose(hFile);

        if (!subdirectories.empty()) {

            handleSubdirectories(directory, subdirectories, depthLevel, runtimeState);
        }
    }
}

void handleDirectory(std::string fileName, std::vector<std::string> &subdirectories, RuntimeState *runtimeState) {

    if (!ignoreDirectory(fileName, runtimeState->getDirectoriesToIgnore())) {

        subdirectories.push_back(fileName);
    }
}

void handleFile(std::string fileName, std::string directory, RuntimeState *runtimeState) {

    std::string fileExtension = PathFindExtension(fileName.c_str());

    if (!ignoreFileByExtension(fileExtension, runtimeState->getExtensionsToIgnore())) {

        if (runtimeState->getOptions() & opts::file_name_match) {

            if (includeFileByFileNameMatch(fileName, runtimeState->getFileNameRegex())) {

                printMatchesInFileAndFileNameIfVerbose(fileName, directory, runtimeState);
            }
        }
        else {

            printMatchesInFileAndFileNameIfVerbose(fileName, directory, runtimeState);
        }
    }
}

void handleSubdirectories(std::string directory,
                          std::vector<std::string> subdirectories,
                          int depthLevel,
                          RuntimeState *runtimeState) {

    depthLevel++;

    if (runtimeState->getOptions() & opts::max_depth) {

        if (depthLevel <= runtimeState->getMaxDepth()) {

            searchFilesInSubdirectories(subdirectories, directory, depthLevel, runtimeState);
        }
    }
    else {

        searchFilesInSubdirectories(subdirectories, directory, depthLevel, runtimeState);
    }
}

void searchFilesInSubdirectories(std::vector<std::string> subdirectories,
                                 std::string directory,
                                 int depthLevel,
                                 RuntimeState *runtimeState) {

    for (int i = 0; i < subdirectories.size(); i++) {

        enumerateAndSearchFiles( (directory +"\\"+ subdirectories[i]), runtimeState, depthLevel);
    }
}

bool ignoreFileByExtension(std::string extension, std::vector<std::string> extensionsToIgnore) {

    for (int i = 0; i < extensionsToIgnore.size(); i++) {

        // use a period beforehand because that's how PathFindExtension behaves
        // otherwise, users have to type a period before every extension
        if (extension.compare(("." + extensionsToIgnore[i])) == 0) {

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

void printMatchesInFileAndFileNameIfVerbose(std::string fileName, std::string directory, RuntimeState *runtimeState) {

    printFileNameIfVerbose(runtimeState, directory, fileName);

    printMatchesInFile( (directory + "\\" + fileName) , runtimeState);
}

bool includeFileByFileNameMatch(std::string fileName, std::regex fileNameRegex) {

    return (std::regex_match(fileName, fileNameRegex));
}

void printFileNameIfVerbose(RuntimeState *runtimeState, std::string directory, std::string fileName) {

    if (runtimeState->getOptions() & opts::verbose) {

        std::cout << (directory + "\\" + fileName) << std::endl;
    }
}
