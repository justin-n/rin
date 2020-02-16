#ifndef RuntimeState_H
#define RuntimeState_H

#include <vector>
#include <string>
#include <regex>

#include "options.h"

class RuntimeState {

    private:

        std::string searchString;

        size_t searchStringLen;

        std::regex searchRegex;

        std::string fileNameToSearch;

        std::string fileNameRegexString;

        std::regex fileNameRegex;

        std::string maxDepthString;

        int maxDepth;

        opts::option_fields options;

        std::vector<std::string> directoriesToIgnore;

        std::vector<std::string> extensionsToIgnore;

    public:

        RuntimeState(
            std::string searchString,
            std::string fileToSearch,
            std::string fileNameRegexString,
            std::string maxDepthString,
            opts::option_fields options,
            std::vector<std::string> directoriesToIgnore,
            std::vector<std::string> extensionsToIgnore
        );

        ~RuntimeState();

        void init();

        std::string getSearchString();

        size_t getSearchStringLen();

        std::regex getSearchRegex();

        std::string getFileNameToSearch();

        std::regex getFileNameRegex();

        int getMaxDepth();

        opts::option_fields getOptions();

        std::vector<std::string> getDirectoriesToIgnore();

        std::vector<std::string> getExtensionsToIgnore();
};

#endif
