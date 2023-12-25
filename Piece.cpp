#include "Piece.hpp"
#include <iostream>

/* static int standardPieces[10][9] = {{0, 1, 0, 1, 1, 1, 0, 1, 0},  // plus
                                    {1, 1, 0, 1, 1, 0, 0, 0, 0},  // square
                                    {1, 0, 0, 1, 1, 0, 0, 0, 0},  // corner
                                    {0, 1, 0, 0, 1, 0, 0, 1, 0},  // line
                                    {0, 1, 1, 1, 1, 0, 0, 0, 0},  // zig-zag
                                    {1, 0, 1, 1, 1, 1, 0, 0, 0},  // U piece
                                    {1, 0, 0, 1, 1, 0, 0, 1, 0},  // step piece
                                    {0, 1, 0, 1, 1, 1, 1, 0, 1},  // up arrow
                                    {1, 0, 0, 1, 1, 1, 0, 0, 1},  // Double zig-zag
                                    {0, 1, 0, 1, 1, 1, 0, 0, 0}}; // pyramid
 */

static int standardPieces[7][16] = {
    {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // I-block
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0}, // j-block
    {0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0}, // L-block
    {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0}, // O-block
    {0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0}, // S-block
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0}, // T-block
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, // Z-block

};

static int colorList[4] = {31, 32, 33, 34};
static int colorIndex = 0;

Piece::Piece(int x, int y)
{

    srand(time(0));

    w = 4;
    h = 4;
    this->x = x;
    this->y = y;
    rotation = 0;

    shapeArr = new int[w * h];
    stdIndex = rand() % 7;

    color = colorList[colorIndex];
    colorIndex = (colorIndex + 1) % 4; // cycling through available colors

    for (int i = 0; i <= w * h; i++)
    {
        shapeArr[i] = standardPieces[stdIndex][i] * color;
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
    case 0:
        return ' ';
        break;
    case 30:
        return '.';
        break;

    default:
        return 'O';
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
                tempArr[index] = shapeArr[w * (w - 1) + i - w * j];
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
                tempArr[index] = shapeArr[(w - 1) - i + w * j];
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