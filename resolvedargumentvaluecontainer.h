#ifndef ResolvedArgumentValueContainer_H
#define ResolvedArgumentValueContainer_H

#include <vector>
#include <string>

#include "options.h"

class ResolvedArgumentValueContainer {

    private:

        std::string searchString;

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

        opts::option_fields getOptions();

        std::vector<std::string> getDirectoriesToIgnore();

        void setDirectoriesToIgnore(std::vector<std::string> directoriesToIgnore);

        std::vector<std::string> getExtensionsToIgnore();
};

#endif
