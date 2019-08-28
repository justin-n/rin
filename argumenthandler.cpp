#include "argumenthandler.h"

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "resolvedargumentvaluecontainer.h"

ArgumentHandler::ArgumentHandler(int argc, char** argv) {

    this->argc = argc;

    this->argv = argv;

    this->resolvedArgumentValueContainer = new ResolvedArgumentValueContainer();
}

ArgumentHandler::~ArgumentHandler() { 

    delete this->resolvedArgumentValueContainer;
}

void ArgumentHandler::init() {

    for (int i = 0; i < this->argc; i++) {

        this->arguments.push_back(argv[i]);
    }

    this->supportedArguments = this->getSupportedArguments();

    this->checkSyntax();

    this->resolvedArgumentValueContainer->setSearchString(this->argv[argc - 1]);

    for (int i = 1; i < ((this->argc) - 1); i++) {

        if (this->getArgumentName(this->arguments.at(i)).compare("ed") == 0) {

            this->loadDirectoriesToIgnore(this->getArgumentValueOf(this->arguments.at(i)));
        }
    }
}

void ArgumentHandler::checkSyntax() {

    if (this->argc == 1) {

        throw std::runtime_error("Please provide at least a string to search");
    }

    if (this->argc > 3) {

        throw std::runtime_error("Too many arguments");
    }

    for (int i = 1; i < (this->argc - 1); i++) {

        if (!isValidArgumentSyntax(arguments.at(i))) {

            throw std::runtime_error("Invalid argument syntax: " + arguments.at(i));
        }
    }

    this->checkForArgumentSupport();
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

std::vector<std::string> ArgumentHandler::getDirectoriesToIgnore() {

    return this->resolvedArgumentValueContainer->getDirectoriesToIgnore();
}

opts::option_fields ArgumentHandler::getOptions() {

    return this->resolvedArgumentValueContainer->getOptions();
}

std::vector<std::string> ArgumentHandler::getExtensionsToIgnore() {

    return this->resolvedArgumentValueContainer->getExtensionsToIgnore();
}

std::vector<std::string> ArgumentHandler::getSupportedArguments() {

    std::vector<std::string> supportedArguments;

    supportedArguments.push_back("ed");

    return supportedArguments;
}

void ArgumentHandler::checkForArgumentSupport() {

    for (int i = 1; i < (this->argc - 1); i++) {

        if (!isSupportedArgument(this->getArgumentName(this->arguments.at(i)))) {

            throw std::runtime_error("Argument not supported: " + arguments.at(i));
        }
    }
}

bool ArgumentHandler::isSupportedArgument(std::string argName) {

    return ( std::find(this->supportedArguments.begin(),
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

    std::vector<std::string> directoriesToIgnore;

    std::vector<std::string> directoryNameList =
                    this->getStringVectorFromStringWithDelimiter(commaDelimitedDirectoryNameList, ",");

    for (int i = 0; i < directoryNameList.size(); i++) {

        std::string directoryName = directoryNameList.at(i);

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
