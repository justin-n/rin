# rin

grep alternative for Windows

Named after the grep options that this program emulates by default:

`-r` Read all files under each directory, recursively.

`-i` Ignore case distinctions in both the PATTERN and the input files.

`-n` Prefix each line of output with the 1-based line number within its input file.

#### Usage

If a filename to search is not provided, files will be searched recursively from the working directory.

    rin [-ed=[dirs]] searchString [FILENAME]

        -ed=[dirs]
            Ignore a comma-separated list of directory names

Supports searching stdout by using the pipe operator:

    <command> | rin [searchString]

#### Other Information

This program does not support patterns, just strings.

It can be compiled in the same directory as all the files with this command:

    g++ -static -o rin rin.cpp runtimestate.cpp cmdcolors.cpp matchprinter.cpp filehandler.cpp pipeoperations.cpp argumenthandler.cpp resolvedargumentvaluecontainer.cpp -lshlwapi

Currently using g++ version 8.1.0 compiled on Windows 10
