#include "argumenthandler.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "resolvedargumentvaluecontainer.h"

ArgumentHandler::ArgumentHandler(int argc, char** argv) : argc(argc), argv(argv) {

    this->resolvedArgumentValueContainer = new ResolvedArgumentValueContainer();
}

ArgumentHandler::~ArgumentHandler() { 

    delete this->resolvedArgumentValueContainer;
}

void ArgumentHandler::init() {

    this->loadArgumentsIntoArgumentsVector();

    this->supportedArguments = this->getSupportedArguments();

    this->checkAndResolveSyntax();

    this->resolveExcludeDirectoryNamesArguments();

    this->resolveRegexSwitch();

    this->resolveVerboseSwitch();

    this->resolveFileNameMatchSwitchAndFileNameRegexString();

    this->resolveMaxDepthSwitchAndMaxDepth();
}

void ArgumentHandler::loadArgumentsIntoArgumentsVector() {

    for (int i = 0; i < this->argc; i++) {

        this->arguments.push_back(this->argv[i]);
    }
}

void ArgumentHandler::checkAndResolveSyntax() {

    this->checkForMinimumNumberOfArguments();

    this->checkForMaximumNumberOfArguments();

    this->resolveSyntax();

    this->checkSyntax();

    this->checkForArgumentSupport();
}

void ArgumentHandler::checkForMinimumNumberOfArguments() {

    if (this->argc == 1) {

        throw std::runtime_error("Please provide at least a string to search");
    }
}

void ArgumentHandler::checkForMaximumNumberOfArguments() {

    if (this->argc > this->MAX_ARGUMENTS) {

        throw std::runtime_error("Too many arguments");
    }
}

void ArgumentHandler::resolveSyntax() {

    if ((this->argc > 2) && (!(this->isValidArgumentSyntax(this->arguments.at(this->argc - 2))))) {

        this->commandSubjectLength = (this->argc - 2);

        this->resolvedArgumentValueContainer->setSearchString(this->arguments.at(this->argc - 2));

        this->resolvedArgumentValueContainer->setFileNameToSearch(this->arguments.at(this->argc - 1));

        this->resolvedArgumentValueContainer->setSearchSingleFileOption(true);
    }
    else {

        this->commandSubjectLength = (this->argc - 1);

        this->resolvedArgumentValueContainer->setSearchString(this->arguments.at(this->argc - 1));
    }
}

void ArgumentHandler::checkSyntax() {

    for (int i = 1; i < this->commandSubjectLength; i++) {

        if (!(this->isValidArgumentSyntax(this->arguments.at(i)))) {

            throw std::runtime_error("Invalid argument syntax: " + this->arguments.at(i));
        }
    }
}

void ArgumentHandler::resolveExcludeDirectoryNamesArguments() {

    for (int i = 1; i < this->commandSubjectLength; i++) {

        if (this->getArgumentName(this->arguments.at(i)).compare("ed") == 0) {

            if (this->resolvedArgumentValueContainer->getOptions() & opts::search_single_file) {

                std::cout << "[WARNING] Ignoring -ed argument" << std::endl;
            }
            else {

                this->loadDirectoriesToIgnore(this->getArgumentValueOf(this->arguments.at(i)));
            }
        }
    }
}

void ArgumentHandler::resolveRegexSwitch() {

    for (int i = 1; i < this->commandSubjectLength; i++) {

        if (this->getArgumentName(this->arguments.at(i)).compare("rgx") == 0) {

            this->resolvedArgumentValueContainer->setRegexSearchOption(true);
        }
    }
}

void ArgumentHandler::resolveVerboseSwitch() {

    for (int i = 1; i < this->commandSubjectLength; i++) {

        if (this->getArgumentName(this->arguments.at(i)).compare("v") == 0) {

            this->resolvedArgumentValueContainer->setVerboseOption(true);
        }
    }
}

void ArgumentHandler::resolveFileNameMatchSwitchAndFileNameRegexString() {

    for (int i = 1; i < this->commandSubjectLength; i++) {

        if (this->getArgumentName(this->arguments.at(i)).compare("in") == 0) {

            this->resolvedArgumentValueContainer->setFileNameMatchOption(true);

            this->resolvedArgumentValueContainer
                    ->setFileNameRegexString(this->getArgumentValueOf(this->arguments.at(i)));
        }
    }
}

void ArgumentHandler::resolveMaxDepthSwitchAndMaxDepth() {

    for (int i = 1; i < this->commandSubjectLength; i++) {

        if (this->getArgumentName(this->arguments.at(i)).compare("md")  == 0)  {

            this->resolvedArgumentValueContainer->setMaxDepthOption(true);

            this->resolvedArgumentValueContainer
                    ->setMaxDepthString(this->getArgumentValueOf(this->arguments.at(i)));
        }
    }
}

bool ArgumentHandler::isValidArgumentSyntax(std::string arg) {

    if ((arg.substr(0, 1).compare("-") == 0) || (arg.substr(0, 2).compare("--") == 0)) {

        return true;
    }

    return false;
}

std::string ArgumentHandler::getSearchString() {

    return this->resolvedArgumentValueContainer->getSearchString();
}

std::string ArgumentHandler::getFileNameToSearch() {

    return this->resolvedArgumentValueContainer->getFileNameToSearch();
}

std::string ArgumentHandler::getFileNameRegexString() {

    return this->resolvedArgumentValueContainer->getFileNameRegexString();
}

std::string ArgumentHandler::getMaxDepthString() {

    return this->resolvedArgumentValueContainer->getMaxDepthString();
}

opts::option_fields ArgumentHandler::getOptions() {

    return this->resolvedArgumentValueContainer->getOptions();
}

std::vector<std::string> ArgumentHandler::getDirectoriesToIgnore() {

    return this->resolvedArgumentValueContainer->getDirectoriesToIgnore();
}

std::vector<std::string> ArgumentHandler::getExtensionsToIgnore() {

    return this->resolvedArgumentValueContainer->getExtensionsToIgnore();
}

std::vector<std::string> ArgumentHandler::getSupportedArguments() {

    std::vector<std::string> supportedArguments;

    supportedArguments.push_back("ed");

    supportedArguments.push_back("rgx");

    supportedArguments.push_back("v");

    supportedArguments.push_back("in");

    supportedArguments.push_back("md");

    return supportedArguments;
}

void ArgumentHandler::checkForArgumentSupport() {

    for (int i = 1; i < this->commandSubjectLength; i++) {

        if (!(this->isSupportedArgument(this->getArgumentName(this->arguments.at(i))))) {

            throw std::runtime_error("Argument not supported: " + arguments.at(i));
        }
    }
}

bool ArgumentHandler::isSupportedArgument(std::string argName) {

    return (std::find(this->supportedArguments.begin(),
                      this->supportedArguments.end(),
                      argName) != this->supportedArguments.end());

}

std::string ArgumentHandler::getArgumentName(std::string arg) {

    if (arg.find("=") == std::string::npos) {

        if (arg.substr(0, 2).compare("--") == 0) {

            return arg.substr(2);
        }
        else if (arg.substr(0, 1).compare("-") == 0) {

            return arg.substr(1);
        }
        else {

            throw std::runtime_error("Unable to find argument name for " + arg);
        }
    }
    else {

        if (arg.substr(0, 2).compare("--") == 0) {
            
            return arg.substr(2, (arg.size() - (arg.size() - arg.find("=")) - 2));
        }
        else if (arg.substr(0, 1).compare("-") == 0) {

            return arg.substr(1, (arg.size() - (arg.size() - arg.find("=")) - 1));
        }
        else {

            throw std::runtime_error("Unable to find argument name for " + arg);
        }
    }
}

std::string ArgumentHandler::getArgumentValueOf(std::string arg) {

    return (arg.substr((arg.find("=") + 1)));
}

void ArgumentHandler::loadDirectoriesToIgnore(std::string commaDelimitedDirectoryNameList) {

    std::vector<std::string> directoriesToIgnore =
                    this->resolvedArgumentValueContainer->getDirectoriesToIgnore();

    std::vector<std::string> additionalDirectoryNames =
                    this->getStringVectorFromStringWithDelimiter(commaDelimitedDirectoryNameList, ",");

    for (int i = 0; i < additionalDirectoryNames.size(); i++) {

        std::string directoryName = additionalDirectoryNames.at(i);

        std::transform(directoryName.begin(), directoryName.end(), directoryName.begin(), ::tolower);

        directoriesToIgnore.push_back(directoryName);
    }

    this->resolvedArgumentValueContainer->setDirectoriesToIgnore(directoriesToIgnore);
}

std::vector<std::string> ArgumentHandler::getStringVectorFromStringWithDelimiter(std::string str, std::string delim) {

    std::vector<std::string> stringVector;

    size_t nextPos;

    bool lastMatchFound = false;

    while (!lastMatchFound) {

        if ((nextPos = str.find(delim)) == std::string::npos) {

            lastMatchFound = true;
        }

        stringVector.push_back(str.substr(0, nextPos));

        if (!lastMatchFound) {

            str = str.substr(nextPos + 1, str.length());
        }
    }

    return stringVector;
}
