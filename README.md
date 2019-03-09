# rin

grep alternative for Windows

Named after the grep defaults that this program emulates.

-r Read all files under each directory, recursively.
-i Ignore case distinctions in both the PATTERN and the input files.
-n Prefix each line of output with the 1-based line number within its input file.

This program does not support patterns, just strings.

It can be compiled in the same directory as all the files like this:

    g++ -static -o rin rin.cpp cmdcolors.h cmdcolors.cpp casemode.h matchprinter.cpp matchprinter.h filehandler.cpp filehandler.h -lshlwapi

Currently testing with g++ version 8.1.0 compiled on Windows 10
