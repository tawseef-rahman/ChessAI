#pragma once
#include "board.h"

class Evaluation
{
public:
    int evaluate(const Board &board, int color);

private:
    int pieceValue(char piece);
};