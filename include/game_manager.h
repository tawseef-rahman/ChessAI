#pragma once
#include "board.h"

class GameManager
{
public:
    GameManager(Board &board) : board(board), currentPlayer(0) {}
    void startGame();

private:
    Board &board;
    int currentPlayer;
    void switchPlayer();
};