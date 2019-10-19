#include "runtimestate.h"

#include <vector>
#include <string>

#include "options.h"

RuntimeState::RuntimeState(

    std::string searchString,
    std::string filenameToSearch,
    opts::option_fields options,
    std::vector<std::string> directoriesToIgnore,
    std::vector<std::string> extensionsToIgnore)

        : searchString(searchString),
          filenameToSearch(filenameToSearch),
          options(options),
          directoriesToIgnore(directoriesToIgnore),
          extensionsToIgnore(extensionsToIgnore) { }

RuntimeState::~RuntimeState() { }

void RuntimeState::init() {

    if (this->options & opts::regex_search) {

        this->searchRegex = std::regex(this->searchString);
    }
    else {

        this->searchStringLen = this->searchString.size();
    }
}

std::string RuntimeState::getSearchString() {
    return this->searchString;
}

size_t RuntimeState::getSearchStringLen() {
    return this->searchStringLen;
}

std::regex RuntimeState::getSearchRegex() {

    return this->searchRegex;
}

std::string RuntimeState::getFilenameToSearch() {
    return this->filenameToSearch;
}

opts::option_fields RuntimeState::getOptions() {
    return this->options;
}

std::vector<std::string> RuntimeState::getDirectoriesToIgnore() {
    return this->directoriesToIgnore;
}

std::vector<std::string> RuntimeState::getExtensionsToIgnore() {
    return this->extensionsToIgnore;
}
