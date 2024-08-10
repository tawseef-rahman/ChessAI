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
    void undoMove(int startRow, int startCol, int endRow, int endCol, Piece *capturedPiece);
    void printBoard() const;
    bool isGameOver() const;
    bool isCheckmate(int color) const;
    bool isStalemate(int color) const;
    bool isInCheck(int color) const;
    bool isMoveLegal(int startRow, int startCol, int endRow, int endCol) const;
    bool canCastle(int color, bool kingside) const;
    void castle(int color, bool kingside);
    void promotePawn(int row, int col, char promotionPiece);
    bool canEnPassant(int startRow, int startCol, int endRow, int endCol) const;
    void enPassant(int startRow, int startCol, int endRow, int endCol);

private:
    std::vector<std::vector<Piece *>> board;
    int halfMoveClock;
    int fullMoveNumber;
    std::pair<int, int> enPassantTarget;
    void initializePieces();
    void clearBoard();
};