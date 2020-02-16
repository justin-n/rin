# rin

grep alternative for Windows

Named after the grep options that this program emulates by default:

`-r` Read all files under each directory, recursively.

`-i` Ignore case distinctions in both the PATTERN and the input files.

`-n` Prefix each line of output with the 1-based line number within its input file.

#### Usage

If a filename to search is not provided, files will be searched recursively from the working directory.

    rin [-ed=[dirs]] [-in=[PATTERN]] [-md=[depth]] [-rgx] [-v] searchString [FILENAME]

        -ed=[dirs]
            Ignore a comma-separated list of directory names. If this
            argument is repeated, the values of each argument will be
            combined.

        -in=[PATTERN]
            Only search files which have a file name matching the
            PATTERN.

        -md=[depth]
            Search directories recursively with a maximum depth of
            the depth provided. Depth is an integer value parsed by
            std::stoi. The current directory has a depth of 0. If a
            negative value is provided, only the current directory
            will be searched.

        -rgx
            searchString will be treated as a regex string. If this
            argument is not included, searchString will be treated as
            a literal string.

        -v
            Verbose output will be used. Currently, each file being
            searched will be printed. This can be useful for finding
            directories that could be ignored to reduce the time of
            long searches.

Supports searching stdout by using the pipe operator:

    <command> | rin [-rgx] [searchString]

#### Other Information

It can be compiled in the same directory as all the files with this command:

    g++ -static -o rin src\*.cpp -lshlwapi

Currently using g++ version 8.1.0 compiled on Windows 10
