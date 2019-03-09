#include <windows.h>
#include "cmdcolors.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void setTextToRed() {
    SetConsoleTextAttribute(hConsole, 12);
}

void setTextToGreen() {
    SetConsoleTextAttribute(hConsole, 10);
}
