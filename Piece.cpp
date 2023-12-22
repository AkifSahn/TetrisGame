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

Piece::Piece(int x, int y)
{

    srand(time(0));

    w = 3;
    h = 3;
    this->x = x;
    this->y = y;
    rotation = 0;

    shapeArr = new int[w * h];
    stdIndex = rand() % 10;

    for (int i = 0; i <= w * h; i++)
    {
        shapeArr[i] = standardPieces[stdIndex][i];
    }
}

Piece::~Piece()
{
    // delete[] shapeArr;
}

char Piece::returnPiece(int key)
{
    switch (key)
    {
    case 1:
        return '#';
        break;
    case 2:
        return 'X';
        break;

    default:
        return ' ';
        break;
    }
}

void Piece::rotatePiece(int r)
{

    int tempArr[w * h]; // Use a fixed-size temporary array

    switch (r)
    {
    case 90:
        rotation = r;
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                int index = i * w + j;
                tempArr[index] = shapeArr[6 + i - 3 * j];
            }
        }
        for (int i = 0; i < w * h; i++)
        {
            shapeArr[i] = tempArr[i];
        }
        break;

    case 270:
        rotation = r;
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                int index = i * w + j;
                tempArr[index] = shapeArr[2 - i + 3 * j];
            }
        }
        for (int i = 0; i < w * h; i++)
        {
            shapeArr[i] = tempArr[i];
        }
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

void Piece::printShape()
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            std::cout << shapeArr[i * w + j] << " ";
        }
        std::cout << std::endl;
    }
}