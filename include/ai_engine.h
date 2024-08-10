#pragma once
#include "board.h"

class AIEngine
{
public:
    AIEngine(int depth) : searchDepth(depth) {}
    std::pair<int, int> chooseBestMove(const Board &board, int color);

private:
    int searchDepth;
    int evaluateBoard(const Board &board, int color);
    int minimax(Board &board, int depth, int alpha, int beta, int color);
    std::vector<std::pair<int, int>> generateLegalMoves(const Board &board, int color);
};