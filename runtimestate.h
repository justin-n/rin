#ifndef RunTimeState_H
#define RunTimeState_H

#include <vector>
#include <string>

#include "options.h"

class RunTimeState {

    private:

        std::string searchString;

        size_t searchStringLen;

        std::string filenameToSearch;

        opts::option_fields options;

        std::vector<std::string> directoriesToIgnore;

        std::vector<std::string> extensionsToIgnore;

    public:

        RunTimeState(
            std::string searchString,
            std::string fileToSearch,
            opts::option_fields options,
            std::vector<std::string> directoriesToIgnore,
            std::vector<std::string> extensionsToIgnore
        );

        ~RunTimeState();

        std::string getSearchString();

        size_t getSearchStringLen();

        std::string getFilenameToSearch();

        opts::option_fields getOptions();

        std::vector<std::string> getDirectoriesToIgnore();

        std::vector<std::string> getExtensionsToIgnore();
};

#endif
