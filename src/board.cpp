#include "../include/board.h"
#include <iostream>

Board::Board()
{
    initializeBoard();
}

void Board::initializeBoard()
{
    clearBoard();
    initializePieces();
    halfMoveClock = 0;
    fullMoveNumber = 1;
    enPassantTarget = {-1, -1};
}

void Board::initializePieces()
{
    for (int i = 0; i < 8; ++i)
    {
        board[1][i] = new Pawn(1);
        board[6][i] = new Pawn(0);
    }

    board[0][0] = new Rook(1);
    board[0][7] = new Rook(1);
    board[0][1] = new Knight(1);
    board[0][6] = new Knight(1);
    board[0][2] = new Bishop(1);
    board[0][5] = new Bishop(1);
    board[0][3] = new Queen(1);
    board[0][4] = new King(1);

    board[7][0] = new Rook(0);
    board[7][7] = new Rook(0);
    board[7][1] = new Knight(0);
    board[7][6] = new Knight(0);
    board[7][2] = new Bishop(0);
    board[7][5] = new Bishop(0);
    board[7][3] = new Queen(0);
    board[7][4] = new King(0);
}

Piece *Board::getPieceAt(int row, int col)
{
    return board[row][col];
}

void Board::movePiece(int startRow, int startCol, int endRow, int endCol)
{
    Piece *piece = getPieceAt(startRow, startCol);
    Piece *capturedPiece = getPieceAt(endRow, endCol);

    if (capturedPiece != nullptr)
    {
        delete capturedPiece;
    }

    board[endRow][endCol] = piece;
    board[startRow][startCol] = nullptr;

    if (piece->getSymbol() == 'P' && endRow == 0)
    {
        promotePawn(endRow, endCol, 'Q');
    }
    else if (piece->getSymbol() == 'p' && endRow == 7)
    {
        promotePawn(endRow, endCol, 'q');
    }

    if (canEnPassant(startRow, startCol, endRow, endCol))
    {
        enPassant(startRow, startCol, endRow, endCol);
    }

    if (piece->getSymbol() == 'P' || piece->getSymbol() == 'p')
    {
        if (abs(startRow - endRow) == 2)
        {
            enPassantTarget = {endRow, endCol};
        }
        else
        {
            enPassantTarget = {-1, -1};
        }
    }
    else
    {
        enPassantTarget = {-1, -1};
    }

    if (piece->getSymbol() == 'K' && abs(startCol - endCol) == 2)
    {
        castle(piece->getColor(), endCol > startCol);
    }

    if (piece->getSymbol() == 'P' || piece->getSymbol() == 'p' || capturedPiece != nullptr)
    {
        halfMoveClock = 0;
    }
    else
    {
        halfMoveClock++;
    }

    if (piece->getColor() == 1)
    {
        fullMoveNumber++;
    }
}

void Board::undoMove(int startRow, int startCol, int endRow, int endCol, Piece *capturedPiece)
{
    Piece *piece = getPieceAt(endRow, endCol);

    board[startRow][startCol] = piece;
    board[endRow][endCol] = capturedPiece;
}

void Board::printBoard() const
{
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            if (board[row][col] != nullptr)
            {
                std::cout << board[row][col]->getSymbol() << " ";
            }
            else
            {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

bool Board::isGameOver() const
{
    return isCheckmate(0) || isCheckmate(1) || isStalemate(0) || isStalemate(1);
}

bool Board::isCheckmate(int color) const
{
    if (isInCheck(color))
    {
        for (int row = 0; row < 8; ++row)
        {
            for (int col = 0; col < 8; ++col)
            {
                Piece *piece = board[row][col];
                if (piece != nullptr && piece->getColor() == color)
                {
                    for (int r = 0; r < 8; ++r)
                    {
                        for (int c = 0; c < 8; ++c)
                        {
                            if (isMoveLegal(row, col, r, c))
                            {
                                Piece *capturedPiece = board[r][c];
                                movePiece(row, col, r, c);
                                bool checkmate = !isInCheck(color);
                                undoMove(row, col, r, c, capturedPiece);

                                if (checkmate)
                                {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
    return false;
}

bool Board::isStalemate(int color) const
{
    if (!isInCheck(color))
    {
        for (int row = 0; row < 8; ++row)
        {
            for (int col = 0; col < 8; ++col)
            {
                Piece *piece = board[row][col];
                if (piece != nullptr && piece->getColor() == color)
                {
                    for (int r = 0; r < 8; ++r)
                    {
                        for (int c = 0; c < 8; ++c)
                        {
                            if (isMoveLegal(row, col, r, c))
                            {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
    return false;
}

bool Board::isInCheck(int color) const
{
    int kingRow, kingCol;
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece *piece = board[row][col];
            if (piece != nullptr && piece->getColor() == color && piece->getSymbol() == ‘K’)
            {
                kingRow = row;
                kingCol = col;
            }
        }
    }

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece *piece = board[row][col];
            if (piece != nullptr && piece->getColor() != color)
            {
                if (isMoveLegal(row, col, kingRow, kingCol))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::isMoveLegal(int startRow, int startCol, int endRow, int endCol) const
{
    Piece *piece = getPieceAt(startRow, startCol);
    Piece *target = getPieceAt(endRow, endCol);

    if (piece == nullptr)
    {
        return false;
    }

    if (target != nullptr && piece->getColor() == target->getColor())
    {
        return false;
    }

    return piece->isMoveValid(startRow, startCol, endRow, endCol, *this);
}

bool Board::canCastle(int color, bool kingside) const
{
    int row = (color == 0) ? 7 : 0;
    if (kingside)
    {
        return getPieceAt(row, 4) != nullptr && getPieceAt(row, 4)->getSymbol() == ‘K’ &&
               getPieceAt(row, 7) != nullptr && getPieceAt(row, 7)->getSymbol() == ‘R’ &&
               getPieceAt(row, 5) == nullptr && getPieceAt(row, 6) == nullptr;
    }
    else
    {
        return getPieceAt(row, 4) != nullptr && getPieceAt(row, 4)->getSymbol() == ‘K’ &&
               getPieceAt(row, 0) != nullptr && getPieceAt(row, 0)->getSymbol() == ‘R’ &&
               getPieceAt(row, 1) == nullptr && getPieceAt(row, 2) == nullptr && getPieceAt(row, 3) == nullptr;
    }
}

void Board::castle(int color, bool kingside)
{
    int row = (color == 0) ? 7 : 0;
    if (kingside)
    {
        movePiece(row, 4, row, 6);
        movePiece(row, 7, row, 5);
    }
    else
    {
        movePiece(row, 4, row, 2);
        movePiece(row, 0, row, 3);
    }
}

void Board::promotePawn(int row, int col, char promotionPiece)
{
    delete board[row][col];

    switch (promotionPiece)
    {
    case 'Q':
    case 'q':
        board[row][col] = new Queen(row < 4 ? 1 : 0);
        break;
    case 'R':
    case 'r':
        board[row][col] = new Rook(row < 4 ? 1 : 0);
        break;
    case 'B':
    case 'b':
        board[row][col] = new Bishop(row < 4 ? 1 : 0);
        break;
    case 'N':
    case 'n':
        board[row][col] = new Knight(row < 4 ? 1 : 0);
        break;
    default:
        board[row][col] = new Queen(row < 4 ? 1 : 0);
        break;
    }
}

bool Board::canEnPassant(int startRow, int startCol, int endRow, int endCol) const
{
    Piece *piece = getPieceAt(startRow, startCol);

    if (piece->getSymbol() == 'P' || piece->getSymbol() == 'p')
    {
        return enPassantTarget.first == endRow && enPassantTarget.second == endCol &&
               getPieceAt(endRow + (piece->getColor() == 0 ? 1 : -1), endCol) != nullptr;
    }

    return false;
}

void Board::enPassant(int startRow, int startCol, int endRow, int endCol)
{
    Piece *piece = getPieceAt(startRow, startCol);

    movePiece(startRow, startCol, endRow, endCol);
    int captureRow = endRow + (piece->getColor() == 0 ? 1 : -1);
    Piece *capturedPiece = getPieceAt(captureRow, endCol);

    if (capturedPiece != nullptr)
    {
        delete capturedPiece;
    }

    board[captureRow][endCol] = nullptr;
}

void Board::clearBoard()
{
    board = std::vector<std::vector<Piece *>>(8, std::vector<Piece *>(8, nullptr));
}