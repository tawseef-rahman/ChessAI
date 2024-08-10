#include "piece.h"
#include "board.h"

bool Pawn::isMoveValid(int startRow, int startCol, int endRow, int endCol, const Board &board) const
{
    int direction = (color == 0) ? -1 : 1;

    if (startCol == endCol && board.getPieceAt(endRow, endCol) == nullptr)
    {
        if (endRow == startRow + direction)
        {
            return true;
        }
        else if (endRow == startRow + 2 * direction && startRow == (color == 0 ? 6 : 1) &&
                 board.getPieceAt(startRow + direction, startCol) == nullptr)
        {
            return true;
        }
    }
    else if (abs(startCol - endCol) == 1 && endRow == startRow + direction && board.getPieceAt(endRow, endCol) != nullptr)
    {
        return true;
    }

    return false;
}

bool Rook::isMoveValid(int startRow, int startCol, int endRow, int endCol, const Board &board) const
{
    if (startRow != endRow && startCol != endCol)
    {
        return false;
    }

    int stepRow = (endRow > startRow) ? 1 : (endRow < startRow) ? -1
                                                                : 0;
    int stepCol = (endCol > startCol) ? 1 : (endCol < startCol) ? -1
                                                                : 0;

    int r = startRow + stepRow;
    int c = startCol + stepCol;

    while (r != endRow || c != endCol)
    {
        if (board.getPieceAt(r, c) != nullptr)
        {
            return false;
        }
        r += stepRow;
        c += stepCol;
    }

    return true;
}

bool Knight::isMoveValid(int startRow, int startCol, int endRow, int endCol, const Board &board) const
{
    int dr = abs(startRow - endRow);
    int dc = abs(startCol - endCol);

    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

bool Bishop::isMoveValid(int startRow, int startCol, int endRow, int endCol, const Board &board) const
{
    if (abs(startRow - endRow) != abs(startCol - endCol))
    {
        return false;
    }

    int stepRow = (endRow > startRow) ? 1 : -1;
    int stepCol = (endCol > startCol) ? 1 : -1;

    int r = startRow + stepRow;
    int c = startCol + stepCol;

    while (r != endRow || c != endCol)
    {
        if (board.getPieceAt(r, c) != nullptr)
        {
            return false;
        }
        r += stepRow;
        c += stepCol;
    }

    return true;
}

bool Queen::isMoveValid(int startRow, int startCol, int endRow, int endCol, const Board &board) const
{
    return Rook(color).isMoveValid(startRow, startCol, endRow, endCol, board) ||
           Bishop(color).isMoveValid(startRow, startCol, endRow, endCol, board);
}

bool King::isMoveValid(int startRow, int startCol, int endRow, int endCol, const Board &board) const
{
    int dr = abs(startRow - endRow);
    int dc = abs(startCol - endCol);

    return dr <= 1 && dc <= 1;
}