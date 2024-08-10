#include "game_manager.h"
#include "ai_engine.h"
#include <iostream>

void GameManager::startGame()
{
    while (!board.isGameOver())
    {
        board.printBoard();
        if (currentPlayer == 0)
        {
            std::cout << "White's turn. Enter move (e.g., e2e4): ";
            std::string move;
            std::cin >> move;

            int startRow = 8 - (move[1] - '0');
            int startCol = move[0] - 'a';
            int endRow = 8 - (move[3] - '0');
            int endCol = move[2] - ‘a’;

            if (board.isMoveLegal(startRow, startCol, endRow, endCol))
            {
                board.movePiece(startRow, startCol, endRow, endCol);
                switchPlayer();
            }
            else
            {
                std::cout << "Illegal move. Try again.\n";
            }
        }
        else
        {
            AIEngine ai(3);
            std::pair<int, int> bestMove = ai.chooseBestMove(board, currentPlayer);
            board.movePiece(bestMove.first / 8, bestMove.first % 8, bestMove.second / 8, bestMove.second % 8);
            switchPlayer();
        }
    }

    std::cout << "Game over!\n";
}

void GameManager::switchPlayer()
{
    currentPlayer = 1 - currentPlayer;
}