#ifndef ResolvedArgumentValueContainer_H
#define ResolvedArgumentValueContainer_H

#include <vector>
#include <string>

#include "options.h"

class ResolvedArgumentValueContainer {

    private:

        std::string searchString;

        std::string filenameToSearch;

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

        std::string getFilenameToSearch();

        void setFilenameToSearch(std::string filenameToSearch);

        opts::option_fields getOptions();

        void setSearchSingleFileOption(bool value);

        void setRegexSearchOption(bool value);

        void setVerboseOption(bool value);

        std::vector<std::string> getDirectoriesToIgnore();

        void setDirectoriesToIgnore(std::vector<std::string> directoriesToIgnore);

        std::vector<std::string> getExtensionsToIgnore();
};

#endif
