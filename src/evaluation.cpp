#include "evaluation.h"

int Evaluation::evaluate(const Board &board, int color)
{
    int score = 0;

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece *piece = board.getPieceAt(row, col);
            if (piece != nullptr)
            {
                score += pieceValue(piece->getSymbol()) * (piece->getColor() == color ? 1 : -1);
            }
        }
    }

    return score;
}

int Evaluation::pieceValue(char piece)
{
    switch (piece)
    {
    case 'P':
    case 'p':
        return 100;
    case 'N':
    case 'n':
        return 300;
    case 'B':
    case 'b':
        return 300;
    case 'R':
    case 'r':
        return 500;
    case 'Q':
    case 'q':
        return 900;
    case 'K':
    case 'k':
        return 10000;
    default:
        return 0;
    }
}