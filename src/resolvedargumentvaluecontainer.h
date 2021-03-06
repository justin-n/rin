#ifndef ResolvedArgumentValueContainer_H
#define ResolvedArgumentValueContainer_H

#include <vector>
#include <string>

#include "options.h"

class ResolvedArgumentValueContainer {

    private:

        std::string searchString;

        std::string fileNameToSearch;

        std::string fileNameRegexString;

        std::string maxDepthString;

        opts::option_fields options;

        std::vector<std::string> directoriesToIgnore;

        std::vector<std::string> extensionsToIgnore;

        opts::option_fields getDefaultOptions();

        std::vector<std::string> getDefaultExtensionsToIgnore();

    public:

        ResolvedArgumentValueContainer();

        ~ResolvedArgumentValueContainer();

        std::string getSearchString();

        void setSearchString(std::string searchString);

        std::string getFileNameToSearch();

        void setFileNameToSearch(std::string fileNameToSearch);

        std::string getFileNameRegexString();

        void setFileNameRegexString(std::string fileNameRegexString);

        std::string getMaxDepthString();

        void setMaxDepthString(std::string maxDepthString);

        opts::option_fields getOptions();

        void setSearchSingleFileOption(bool value);

        void setRegexSearchOption(bool value);

        void setVerboseOption(bool value);

        void setNegativeSearchOption(bool value);

        void setFileNameMatchOption(bool value);

        void setMaxDepthOption(bool value);

        std::vector<std::string> getDirectoriesToIgnore();

        void setDirectoriesToIgnore(std::vector<std::string> directoriesToIgnore);

        std::vector<std::string> getExtensionsToIgnore();

        void setExtensionsToIgnore(std::vector<std::string> extensionsToIgnore);
};

#endif
