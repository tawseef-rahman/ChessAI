#pragma once
#include <vector>

class Board;

class Piece
{
public:
    Piece(int color) : color(color) {}
    virtual ~Piece() {}

    int getColor() const { return color; }
    virtual char getSymbol() const = 0;
    virtual bool isMoveValid(int startRow, int startCol, int endRow, int endCol, const Board &board) const = 0;

protected:
    int color;
};

class Pawn : public Piece
{
public:
    Pawn(int color) : Piece(color) {}
    char getSymbol() const override { return color == 0 ? 'P' : 'p'; }
    bool isMoveValid(int startRow, int startCol, int endRow, int endCol, const Board &board) const override;
};

class Rook : public Piece
{
public:
    Rook(int color) : Piece(color) {}
    char getSymbol() const override { return color == 0 ? 'R' : 'r'; }
    bool isMoveValid(int startRow, int startCol, int endRow, int endCol, const Board &board) const override;
};

class Knight : public Piece
{
public:
    Knight(int color) : Piece(color) {}
    char getSymbol() const override { return color == 0 ? 'N' : 'n'; }
    bool isMoveValid(int startRow, int startCol, int endRow, int endCol, const Board &board) const override;
};

class Bishop : public Piece
{
public:
    Bishop(int color) : Piece(color) {}
    char getSymbol() const override { return color == 0 ? 'B' : 'b'; }
    bool isMoveValid(int startRow, int startCol, int endRow, int endCol, const Board &board) const override;
};

class Queen : public Piece
{
public:
    Queen(int color) : Piece(color) {}
    char getSymbol() const override { return color == 0 ? 'Q' : 'q'; }
    bool isMoveValid(int startRow, int startCol, int endRow, int endCol, const Board &board) const override;
};

class King : public Piece
{
public:
    King(int color) : Piece(color) {}
    char getSymbol() const override { return color == 0 ? 'K' : 'k'; }
    bool isMoveValid(int startRow, int startCol, int endRow, int endCol, const Board &board) const override;
};