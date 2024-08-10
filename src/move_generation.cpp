#include "move_generation.h"

std::vector<std::pair<int, int>> MoveGeneration::generateAllLegalMoves(const Board &board, int color)
{
    std::vector<std::pair<int, int>> legalMoves;

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece *piece = board.getPieceAt(row, col);
            if (piece != nullptr && piece->getColor() == color)
            {
                for (int r = 0; r < 8; ++r)
                {
                    for (int c = 0; c < 8; ++c)
                    {
                        if (board.isMoveLegal(row, col, r, c))
                        {
                            legalMoves.push_back({row * 8 + col, r * 8 + c});
                        }
                    }
                }
            }
        }
    }

    return legalMoves;
}