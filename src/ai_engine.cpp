#include "ai_engine.h"
#include "evaluation.h"
#include <algorithm>

Move AIEngine::chooseBestMove(Board &board, int depth)
{
    int bestScore = -100000;
    Move bestMove;

    std::vector<Move> moves = generateMoves(board, 1);

    for (const Move &move : moves)
    {
        board.movePiece(move.startRow, move.startCol, move.endRow, move.endCol);
        int score = minimax(board, depth - 1, -100000, 100000, false);
        board.movePiece(move.endRow, move.endCol, move.startRow, move.startCol);

        if (score > bestScore)
        {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}

int AIEngine::minimax(Board &board, int depth, int alpha, int beta, bool isMaximizingPlayer)
{
    if (depth == 0 || board.isGameOver())
    {
        return evaluateBoard(board);
    }

    if (isMaximizingPlayer)
    {
        int maxEval = -100000;
        std::vector<Move> moves = generateMoves(board, 1);
        for (const Move &move : moves)
        {
            board.movePiece(move.startRow, move.startCol, move.endRow, move.endCol);
            int eval = minimax(board, depth - 1, alpha, beta, false);
            board.movePiece(move.endRow, move.endCol, move.startRow, move.startCol);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
                break;
        }
        return maxEval;
    }
    else
    {
        int minEval = 100000;
        std::vector<Move> moves = generateMoves(board, 0);
        for (const Move &move : moves)
        {
            board.movePiece(move.startRow, move.startCol, move.endRow, move.endCol);
            int eval = minimax(board, depth - 1, alpha, beta, true);
            board.movePiece(move.endRow, move.endCol, move.startRow, move.startCol);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}