#include "argumenthandler.h"

#include <vector>
#include <string>

#include <iostream>

ArgumentHandler::ArgumentHandler(int argc, char** argv) {

    this->argc = argc;

    this->argv = argv;
}

ArgumentHandler::~ArgumentHandler() { }

void ArgumentHandler::init() {

    for (int i = 0; i < this->argc; i++) {

        this->arguments.push_back(argv[i]);
    }

    this->checkSyntax();

    this->supportedArguments = this->getSupportedArguments();
}

void ArgumentHandler::checkSyntax() {

    if (argc == 1) {

        throw std::runtime_error("Please provide at least a string to search");
    }

    if (argc > 3) {

        throw std::runtime_error("Too many arguments");
    }

    for (int i = 1; i < argc; i++) {

        if (i < (argc - 1)) {
            
            if (!isValidArgumentSyntax(arguments.at(i))) {

                throw std::runtime_error("Invalid argument syntax: " + arguments.at(i));
            }
        }
    }
}

std::vector<std::string> ArgumentHandler::getArguments() {

    return this->arguments;
}

int ArgumentHandler::getNumberOfArguments() {

    return this->argc;
}

bool ArgumentHandler::isValidArgumentSyntax(std::string arg) {

    if (((arg.find("=") == std::string::npos)) || (arg.substr(0, 1).compare("-") != 0)) {

        return false;
    }

    return true;
}

std::vector<std::string> ArgumentHandler::getSupportedArguments() {

    std::vector<std::string> supportedArguments;

    supportedArguments.push_back("ed");

    return supportedArguments;
}
