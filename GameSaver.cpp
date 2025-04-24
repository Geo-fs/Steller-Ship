#include "GameSaver.h"
#include "GameLogger.h"
#include <iostream>
#include <filesystem>
#include "tools.h"
#include "gameNumber.h"
#include "intro.h"
#include "GameState.h"

void GameSaver::saveGame(const GameState& state) {
    std::filesystem::create_directory("Savedgame");
    if (state.saveToFile("Savedgame/SavedGameRecent")) {
        GameLogger::getInstance().log("Game saved successfully.", LogLevel::INFO);
    }
    else {
        GameLogger::getInstance().log("Failed to save game.", LogLevel::ERROR);
    }
}

GameState GameSaver::loadGame() {
    GameState state;
    if (state.loadFromFile("Savedgame/SavedGameRecent")) {
        GameLogger::getInstance().log("Game loaded successfully.", LogLevel::INFO);
    }
    else {
        GameLogger::getInstance().log("Failed to load saved game. Returning default state.", LogLevel::WARNING);
    }
    return state;
}
