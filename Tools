#pragma once
// .h
#include <string>
#include "GameLogger.h"
#include "Windows.h"
#include <thread>
class tools {
public:
    const char toUpperCase(const char& c) {
        return std::toupper(c);
    }

    std::string toupperstring(std::string& str) {
        std::string temp;
        for (const auto& s : str) {
            temp += toUpperCase(s);
        }
        return temp;
    }
};

static void delay(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

static void clearConsole() {
#ifdef _WIN32
    // For Windows
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };

    if (hStdOut == INVALID_HANDLE_VALUE) return;

    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    SetConsoleCursorPosition(hStdOut, homeCoords);
#else
    // For Unix-like systems (Linux, macOS)
    std::system("clear");
#endif
}
