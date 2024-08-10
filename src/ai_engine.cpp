#include "ai_engine.h"
#include "move_generation.h"
#include "evaluation.h"

std::pair<int, int> AIEngine::chooseBestMove(const Board &board, int color)
{
    int bestScore = (color == 0) ? -9999 : 9999;
    std::pair<int, int> bestMove = {-1, -1};

    std::vector<std::pair<int, int>> legalMoves = generateLegalMoves(board, color);

    for (const auto &move : legalMoves)
    {
        Board tempBoard = board;
        tempBoard.movePiece(move.first / 8, move.first % 8, move.second / 8, move.second % 8);

        int score = minimax(tempBoard, searchDepth - 1, -9999, 9999, color == 0 ? 1 : 0);

        if ((color == 0 && score > bestScore) || (color == 1 && score < bestScore))
        {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}

int AIEngine::evaluateBoard(const Board &board, int color)
{
    Evaluation eval;
    return eval.evaluate(board, color);
}

int AIEngine::minimax(Board &board, int depth, int alpha, int beta, int color)
{
    if (depth == 0 || board.isGameOver())
    {
        return evaluateBoard(board, color);
    }

    std::vector<std::pair<int, int>> legalMoves = generateLegalMoves(board, color);

    if (color == 0)
    {
        int maxEval = -9999;
        for (const auto &move : legalMoves)
        {
            Board tempBoard = board;
            tempBoard.movePiece(move.first / 8, move.first % 8, move.second / 8, move.second % 8);
            int eval = minimax(tempBoard, depth - 1, alpha, beta, 1);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
            {
                break;
            }
        }
        return maxEval;
    }
    else
    {
        int minEval = 9999;
        for (const auto &move : legalMoves)
        {
            Board tempBoard = board;
            tempBoard.movePiece(move.first / 8, move.first % 8, move.second / 8, move.second % 8);
            int eval = minimax(tempBoard, depth - 1, alpha, beta, 0);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
            {
                break;
            }
        }
        return minEval;
    }
}

std::vector<std::pair<int, int>> AIEngine::generateLegalMoves(const Board &board, int color)
{
    MoveGeneration moveGen;
    return moveGen.generateAllLegalMoves(board, color);
}