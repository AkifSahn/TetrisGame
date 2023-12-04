#include "Piece.hpp"

Piece::Piece()
{
    srand(time(0));
    shape = pieceType(rand() % NUMOFPIECE);
    rotation = 0;
}

bool Piece::rotate(int rot)
{
    rot = (rot < 0) ? rot * -1 : rot;
    rotation += rot;
    rotation = rotation % 4;

    return true;
}