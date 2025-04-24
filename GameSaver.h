#pragma once
#ifndef GAMESAVER_H
#define GAMESAVER_H

#include "GameState.h"

class GameSaver {
public:
    static void saveGame(const GameState& state);
    static GameState loadGame();
};

#endif // GAMESAVER_H
