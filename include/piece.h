#pragma once

class Piece
{
public:
    Piece(int color) : color(color) {}
    virtual ~Piece() = default;
    virtual char getSymbol() const = 0;
    int getColor() const { return color; }

protected:
    int color;
};

class Pawn : public Piece
{
public:
    Pawn(int color) : Piece(color) {}
    char getSymbol() const override
    {
        return (color == 0) ? 'P' : 'p';
    }
};