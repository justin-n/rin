#include "runtimestate.h"

#include <vector>
#include <string>

#include "options.h"

RuntimeState::RuntimeState(

    std::string searchString,
    std::string fileNameToSearch,
    std::string fileNameRegexString,
    opts::option_fields options,
    std::vector<std::string> directoriesToIgnore,
    std::vector<std::string> extensionsToIgnore)

        : searchString(searchString),
          fileNameToSearch(fileNameToSearch),
          fileNameRegexString(fileNameRegexString),
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

    if (this->options & opts::file_name_match) {

        this->fileNameRegex = std::regex(this->fileNameRegexString);
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

std::string RuntimeState::getFileNameToSearch() {
    return this->fileNameToSearch;
}

std::string RuntimeState::getFileNameRegexString() {
    return this->fileNameRegexString;
}

std::regex RuntimeState::getFileNameRegex() {
    return this->fileNameRegex;
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
