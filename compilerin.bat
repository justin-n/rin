@echo off

g++ -static -o rin rin.cpp cmdcolors.h cmdcolors.cpp matchprinter.cpp matchprinter.h filehandler.cpp filehandler.h options.h -lshlwapi
