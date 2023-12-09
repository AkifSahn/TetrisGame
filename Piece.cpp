#include "Piece.hpp"

Piece::Piece()
{

    srand(time(0));

    w = 3;
    h = 3;
    x = 0;
    y = 0;
    rotation = 0;

    // shapeArr = new int[w * h];
    stdIndex = rand() % 10;
    shapeArr = standardPieces[stdIndex];
}

Piece::~Piece()
{
    delete shapeArr;
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

void Piece::rotatePiece(int r)
{

    switch (r)
    {
    case 0:
        rotation = r;
        shapeArr = standardPieces[stdIndex];
        break;
    case 90:
        rotation = r;
        int *tempArr = new int[w * h];
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                int index = i * w + j;
                tempArr[index] = shapeArr[6 + i - 3 * j];
            }
        }
        delete tempArr;
        break;

    default:
        break;
    }
}