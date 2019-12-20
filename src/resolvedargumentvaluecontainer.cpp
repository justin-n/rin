#include "resolvedargumentvaluecontainer.h"

#include <vector>
#include <string>

#include "options.h"

ResolvedArgumentValueContainer::ResolvedArgumentValueContainer() {

    this->options = this->getDefaultOptions();

    this->extensionsToIgnore = this->getDefaultExtensionsToIgnore();
}

ResolvedArgumentValueContainer::~ResolvedArgumentValueContainer() { }

std::string ResolvedArgumentValueContainer::getSearchString() {

    return this->searchString;
}

void ResolvedArgumentValueContainer::setSearchString(std::string searchString) {

    this->searchString = searchString;
}

std::string ResolvedArgumentValueContainer::getFilenameToSearch() {

    return this->filenameToSearch;
}

void ResolvedArgumentValueContainer::setFilenameToSearch(std::string filenameToSearch) {

    this->filenameToSearch = filenameToSearch;
}

void ResolvedArgumentValueContainer::setSearchSingleFileOption(bool value) {

    if (value == true) {

        this->options |= opts::search_single_file;
    }
    else {

        this->options &= (~(opts::search_single_file));
    }
}

void ResolvedArgumentValueContainer::setRegexSearchOption(bool value) {

    if (value == true) {

        this->options |= opts::regex_search;
    }
    else {

        this->options &= (~(opts::regex_search));
    }
}

void ResolvedArgumentValueContainer::setVerboseOption(bool value) {

    if (value == true) {

        this->options |= opts::verbose;
    }
    else {

        this->options &= (~(opts::verbose));
    }
}

opts::option_fields ResolvedArgumentValueContainer::getOptions() {

    return this->options;
}

std::vector<std::string> ResolvedArgumentValueContainer::getDirectoriesToIgnore() {

    return this->directoriesToIgnore;
}

void ResolvedArgumentValueContainer::setDirectoriesToIgnore(std::vector<std::string> directoriesToIgnore) {

    this->directoriesToIgnore = directoriesToIgnore;
}

std::vector<std::string> ResolvedArgumentValueContainer::getExtensionsToIgnore() {

    return this->extensionsToIgnore;
}

opts::option_fields ResolvedArgumentValueContainer::getDefaultOptions() {

    opts::option_fields options = 0x0;

    options |= opts::recursive;
    options |= opts::ignore_case;
    options |= opts::print_line_numbers;

    return options;
}

std::vector<std::string> ResolvedArgumentValueContainer::getDefaultExtensionsToIgnore() {

    std::vector<std::string> extensionsToIgnore;

    extensionsToIgnore.push_back(".exe");
    extensionsToIgnore.push_back(".dll");
    extensionsToIgnore.push_back(".class");
    extensionsToIgnore.push_back(".jar");
    extensionsToIgnore.push_back(".zip");
    extensionsToIgnore.push_back(".swc");

    return extensionsToIgnore;
}
