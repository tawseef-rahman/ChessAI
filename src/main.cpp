#include "board.h"
#include "ai_engine.h"
#include "game_manager.h"
#include <iostream>

int main()
{
    Board board;
    GameManager gameManager(board);

    gameManager.startGame();

    return 0;
}