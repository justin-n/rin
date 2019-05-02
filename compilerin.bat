@echo off

g++ -static -o rin rin.cpp runtimestate.cpp cmdcolors.cpp matchprinter.cpp filehandler.cpp pipeoperations.cpp -lshlwapi
