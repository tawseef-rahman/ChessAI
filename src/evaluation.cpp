#include "evaluation.h"

int evaluateBoard(const Board &board)
{
    int score = 0;

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece *piece = board.getPieceAt(row, col);
            if (piece != nullptr)
            {
                if (piece->getColor() == 0)
                {
                    score += 1;
                }
                else
                {
                    score -= 1;
                }
            }
        }
    }

    return score;
}