

#include <iostream>
#include <string>
#include <chrono>
#include <map> 
#include <thread>
#include <cctype>
#include <vector>
#include <utility> 
#include <random>
#include "header.h"
#include "tools.h"
#include "intro.h"
#ifdef _WIN32
#include <windows.h>
#else
#include "GameLogger.h"
#include <cstdlib>
#endif
#include <unordered_map>
#include <sstream>
#include "GameSaver.h"
#include "GameState.h"

GameSaver gameSaver;
GameState currentState; // Assume this holds the current game state

char input;
std::cin >> input;

if (input == 's' || input == 'S') {
    gameSaver.saveGame(currentState);
    // Code to return to the main menu
}


//placeholder


tools g_tools;
intro g_intro;

int main() {
    ///print_intro = &intro::printSkippedIntro;
    GameLogger logger("stellar_ship_log.txt");
    logger.logAction("Game started");
    intro::printSkippedIntro();
    g_intro.printMainIntro();

    std::string skipIntro;
    std::cin >> skipIntro;

    if (skipIntro == "Y" || skipIntro == "y") {
        g_intro.printIntro();
    }
    else {
        g_intro.printSkippedIntro();
    }

    std::cout << "Welcome aboard the STELLER-SHIP! Your space adventure begins now!\n";

    GameManager gameManager;
    gameManager.run();



    return 0;
}
