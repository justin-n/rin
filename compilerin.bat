@echo off

g++ -static -o rin rin.cpp cmdcolors.h cmdcolors.cpp casemode.h matchprinter.cpp matchprinter.h filehandler.cpp filehandler.h -lshlwapi
