#include "Piece.hpp"

Piece::Piece()
{
    w = 3;
    h = 3;
    x = 0;
    y = 0;

    shapeArr = {0,
                1,
                0,
                1,
                1,
                1,
                0,
                1,
                0};
}

char Piece::returnPiece(int key)
{
    switch (key)
    {
    case 1:
        return '#';
        break;

    default:
        return ' ';
        break;
    }
}