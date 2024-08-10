#include "board.h"
#include <iostream>

Board::Board()
{
    initializeBoard();
}

void Board::initializeBoard()
{
    board.resize(8, std::vector<Piece *>(8, nullptr));
    for (int i = 0; i < 8; ++i)
    {
        board[1][i] = new Pawn(1);
        board[6][i] = new Pawn(0);
    }
}

Piece *Board::getPieceAt(int row, int col)
{
    return board[row][col];
}

void Board::movePiece(int startRow, int startCol, int endRow, int endCol)
{
    Piece *piece = getPieceAt(startRow, startCol);
    board[endRow][endCol] = piece;
    board[startRow][startCol] = nullptr;
}

void Board::printBoard() const
{
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            if (board[row][col] != nullptr)
            {
                std::cout << board[row][col]->getSymbol() << " ";
            }
            else
            {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

bool Board::isGameOver() const
{
    return false;
}