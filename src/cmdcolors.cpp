#include "cmdcolors.h"

#include <windows.h>

WORD getUserTextAttributes();
void setTextToRed();
void setTextToGreen();
void setTextToUserColor();

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

WORD userTextAttributes = getUserTextAttributes();

WORD getUserTextAttributes() {

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(hConsole, &csbi);

    WORD userTextAttributes = csbi.wAttributes;

    return userTextAttributes;
}

void setTextToRed() {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void setTextToGreen() {
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void setTextToUserColor() {
    SetConsoleTextAttribute(hConsole, userTextAttributes);
}
