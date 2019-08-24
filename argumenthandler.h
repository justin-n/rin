#ifndef ArgumentHandler_H
#define ArgumentHandler_H

#include <vector>
#include <string>

class ArgumentHandler {

    private:

        int argc;

        char** argv;

        std::vector<std::string> arguments;

        std::vector<std::string> supportedArguments;

        std::string searchString;

        std::vector<std::string> directoriesToIgnore;

        void checkSyntax();

        bool isValidArgumentSyntax(std::string arg);

        std::vector<std::string> getSupportedArguments();

    public:

        ArgumentHandler(int argc, char** argv);

        ~ArgumentHandler();

        void init();

        std::vector<std::string> getArguments();

        int getNumberOfArguments();

};

#endif
