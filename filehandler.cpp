#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <windows.h>
#include <shlwapi.h>

#include "filehandler.h"
#include "matchprinter.h"

void enumerateAndSearchFiles(
        std::string directory, 
        std::string searchString,
        std::vector<std::string> extensionsToIgnore,
        int depthLevel) {

    WIN32_FIND_DATA wfd;

    HANDLE hFile = INVALID_HANDLE_VALUE;

    std::string allFilesInDirectory;

    allFilesInDirectory = directory + "\\*";

    hFile = FindFirstFile(allFilesInDirectory.c_str(), &wfd);

    // std::cout << hFile << std::endl;

    if (hFile != INVALID_HANDLE_VALUE) {

        std::vector<std::string> subDirectories;

        do {

            std::string fileName = wfd.cFileName;

            if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                
                if ((fileName.compare(".")) != 0 && (fileName.compare(".."))) {

                    subDirectories.push_back(fileName);
                }
            }
            else {

                std::string fileExtension = PathFindExtension(fileName.c_str());

                if (!ignoreFile(fileExtension, extensionsToIgnore)) {

                    // printDepthLevel(depthLevel);

                    // std::cout << directory << "\\" << fileName << " <FILE>" << std::endl;

                    // std::cout << fileExtension << std::endl;

                    printMatchesInFile(searchString, directory + "\\" + fileName);

                }
            }

        } while (FindNextFile(hFile, &wfd));

        FindClose(hFile);

        if (!subDirectories.empty()) {

            depthLevel++;
            
            for (int i = 0; i < subDirectories.size(); i++) {

                // printDepthLevel(depthLevel - 1);

                // std::cout << directory << "\\" << subDirectories[i] << " <DIR>" << std::endl;

                enumerateAndSearchFiles(directory +"\\"+ subDirectories[i], searchString, extensionsToIgnore, depthLevel);
            }
        }
    }
}

bool ignoreFile(std::string extension, std::vector<std::string> extensionsToIgnore) {

    for (int i = 0; i < extensionsToIgnore.size(); i++) {
        
        if (extension.compare(extensionsToIgnore[i]) == 0) {

            return true;

        }

    }

    return false;

}

void printDepthLevel(int depthLevel) {
    for (int i = 0; i < depthLevel; i++) {
        std::cout << "    ";
    }
}
