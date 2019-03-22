# rin

grep alternative for Windows

Named after the grep options that this program emulates by default:

`-r` Read all files under each directory, recursively.

`-i` Ignore case distinctions in both the PATTERN and the input files.

`-n` Prefix each line of output with the 1-based line number within its input file.

Supports searching stdout by using the pipe operator:

    <command> | rin [searchString]

This program does not support patterns, just strings.

It can be compiled in the same directory as all the files like this:

    g++ -static -o rin rin.cpp cmdcolors.h cmdcolors.cpp matchprinter.cpp matchprinter.h filehandler.cpp filehandler.h pipeoperations.cpp pipeoperations.h options.h -lshlwapi

Currently using g++ version 8.1.0 compiled on Windows 10
