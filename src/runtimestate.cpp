#include "runtimestate.h"

#include <vector>
#include <string>

#include "options.h"

RunTimeState::RunTimeState(

    std::string searchString,
    std::string filenameToSearch,
    opts::option_fields options,
    std::vector<std::string> directoriesToIgnore,
    std::vector<std::string> extensionsToIgnore)

        : searchString(searchString),
          filenameToSearch(filenameToSearch),
          options(options),
          directoriesToIgnore(directoriesToIgnore),
          extensionsToIgnore(extensionsToIgnore) {

    this->searchStringLen = searchString.size();
}

RunTimeState::~RunTimeState() { }

std::string RunTimeState::getSearchString() {
    return this->searchString;
}

size_t RunTimeState::getSearchStringLen() {
    return this->searchStringLen;
}

std::string RunTimeState::getFilenameToSearch() {
    return this->filenameToSearch;
}

opts::option_fields RunTimeState::getOptions() {
    return this->options;
}

std::vector<std::string> RunTimeState::getDirectoriesToIgnore() {
    return this->directoriesToIgnore;
}

std::vector<std::string> RunTimeState::getExtensionsToIgnore() {
    return this->extensionsToIgnore;
}
