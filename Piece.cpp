#include "Piece.hpp"
#include <iostream>

int standardPieces[10][9] = {{0, 1, 0, 1, 1, 1, 0, 1, 0},  // plus
                             {1, 1, 0, 1, 1, 0, 0, 0, 0},  // square
                             {1, 0, 0, 1, 1, 0, 0, 0, 0},  // corner
                             {0, 1, 0, 0, 1, 0, 0, 1, 0},  // line
                             {0, 1, 1, 1, 1, 0, 0, 0, 0},  // zig-zag
                             {1, 0, 1, 1, 1, 1, 0, 0, 0},  // U piece
                             {1, 0, 0, 1, 1, 0, 0, 1, 0},  // step piece
                             {0, 1, 0, 1, 1, 1, 1, 0, 1},  // up arrow
                             {1, 0, 0, 1, 1, 1, 0, 0, 1},  // Double zig-zag
                             {0, 1, 0, 1, 1, 1, 0, 0, 0}}; // pyramid

Piece::Piece()
{

    srand(time(0));

    w = 3;
    h = 3;
    x = 3;
    y = 0;
    rotation = 0;

    // shapeArr = new int[w * h];
    stdIndex = rand() % 10;
    shapeArr = standardPieces[stdIndex];
}

Piece::~Piece()
{
    // delete shapeArr;
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
        shapeArr = tempArr;
        break;
    }
}

void Piece::moveTo(int newx, int newy)
{
    x = newx;
    y = newy;
}

void Piece::updatePiece()
{
    y++;
}

int Piece::getIndex(int boardWidth)
{
    return y * boardWidth + x;
}

int *Piece::getShape()
{
    return shapeArr;
}

int Piece::getW()
{
    return w;
}

int Piece::getH()
{
    return h;
}

int Piece::getY()
{
    return y;
}

int Piece::getX()
{
    return x;
}