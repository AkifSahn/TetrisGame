#include "Piece.hpp"
#include <iostream>

static int standardPieces[10][16];

static int colorList[4] = {36, 32, 33, 34};
static int colorIndex = 0;

Piece::Piece(int x, int y, int pieceNumber)
{
    // readPieceFile();

    srand(time(0));

    w = 4;
    h = 4;
    this->x = x;
    this->y = y;
    rotation = 0;

    shapeArr = new int[w * h];
    stdIndex = rand() % pieceNumber;

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

void Piece::readPieceFile(int numOfPiece)
{
    std::fstream file;
    file.open("pieces.txt", std::ios::in);
    if (file.is_open())
    {
        std::string tp;
        int index = 0;
        int pieceIndex = 0;
        while (index < numOfPiece)
        {
            getline(file, tp);

            pieceIndex = 0;
            for (int i = 0; i < tp.length(); i++)
            {
                if (tp[i] == '0' || tp[i] == '1')
                {
                    standardPieces[index][pieceIndex] = int(tp[i]) - 48;
                    pieceIndex++;
                }
            }

            index++;
        }
    }
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