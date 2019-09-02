#ifndef ArgumentHandler_H
#define ArgumentHandler_H

#include <vector>
#include <string>

#include "resolvedargumentvaluecontainer.h"

class ArgumentHandler {

    private:

        static const int MAX_ARGUMENTS = 5;

        int argc;

        char** argv;

        std::vector<std::string> arguments;

        std::vector<std::string> supportedArguments;

        int commandSubjectLength;

        ResolvedArgumentValueContainer *resolvedArgumentValueContainer;

        void loadArgumentsIntoArgumentsVector();

        void checkAndResolveSyntax();

        void checkForMinimumNumberOfArguments();

        void checkForMaximumNumberOfArguments();

        void resolveSyntax();

        void checkSyntax();

        void resolveExcludeDirectoryNamesArguments();

        bool isValidArgumentSyntax(std::string arg);

        std::vector<std::string> getSupportedArguments();

        void checkForArgumentSupport();

        bool isSupportedArgument(std::string argName);

        std::string getArgumentName(std::string arg);

        std::string getArgumentValueOf(std::string arg);

        void loadDirectoriesToIgnore(std::string commaDelimitedDirectoryNameList);

        std::vector<std::string> getStringVectorFromStringWithDelimiter(std::string str, std::string delim);

    public:

        ArgumentHandler(int argc, char** argv);

        ~ArgumentHandler();

        void init();

        std::string getSearchString();

        std::string getFilenameToSearch();

        opts::option_fields getOptions();

        std::vector<std::string> getDirectoriesToIgnore();

        std::vector<std::string> getExtensionsToIgnore();
};

#endif
