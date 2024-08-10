#pragma once
#include "board.h"
#include <vector>
#include <utility>

class MoveGeneration
{
public:
    std::vector<std::pair<int, int>> generateAllLegalMoves(const Board &board, int color);
};