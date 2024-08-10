#pragma once
#include <vector>
#include "piece.h"

class Board
{
public:
    Board();
    void initializeBoard();
    Piece *getPieceAt(int row, int col);
    void movePiece(int startRow, int startCol, int endRow, int endCol);
    void printBoard() const;
    bool isGameOver() const;

private:
    std::vector<std::vector<Piece *>> board;
};