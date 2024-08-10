#pragma once
#include "board.h"
#include "ai_engine.h"

class GameManager
{
public:
    GameManager(Board &board);
    void startGame();

private:
    Board &board;
    AIEngine aiEngine;

    void playerTurn();
    void aiTurn();
};