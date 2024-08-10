#include "game_manager.h"
#include <iostream>

GameManager::GameManager(Board &board) : board(board) {}

void GameManager::startGame()
{
    while (!board.isGameOver())
    {
        board.printBoard();
        playerTurn();
        if (board.isGameOver())
            break;
        aiTurn();
    }
}

void GameManager::playerTurn()
{
    int startRow, startCol, endRow, endCol;
    std::cout << "Enter your move (startRow startCol endRow endCol): ";
    std::cin >> startRow >> startCol >> endRow >> endCol;
    board.movePiece(startRow, startCol, endRow, endCol);
}

void GameManager::aiTurn()
{
    std::cout << "AI is thinking... " << std::endl;
    Move bestMove = aiEngine.chooseBestMove(board, 3);
    board.movePiece(bestMove.startRow, bestMove.startCol, bestMove.endRow, bestMove.endCol);
}