#pragma once
#include "board.h"
#include "move_generation.h"

class AIEngine
{
public:
    Move chooseBestMove(Board &board, int depth);

private:
    int minimax(Board &board, int depth, int alpha, int beta, bool isMaximizingPlayer);
};