#pragma once
#include "board.h"
#include <vector>

struct Move
{
    int startRow, startCol;
    int endRow, endCol;
};

std::vector<Move> generateMoves(const Board &board, int color);