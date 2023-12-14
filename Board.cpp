#include "Board.hpp"

Board::Board() : w(20), h(20)
{
    // empty frame, with boundaries
    currentPiece = nullptr;
    frameArray = new int[w * h];
    clearFrame();
}
Board::~Board()
{
    delete currentPiece;
    delete[] frameArray;
}

void Board::clearFrame()
{
    int index;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            index = i * w + j;

            if (j == 0 || j == w - 1 || i == h - 1)
            {
                frameArray[index] = 1;
                continue;
            }

            frameArray[index] = 0; // i = y*w + x
        }
    }
}

Piece Board::createPiece()
{

    currentPiece = nullptr;

    currentPiece = new Piece(7, 0);
    pieces.pushBack(currentPiece);
    return *currentPiece;
}

void Board::renderFrame()
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int index = i * w + j;
            cout << Piece::returnPiece(frameArray[index]);
        }
        cout << endl;
    }
}

void Board::updateBoard()
{

    for (int i = 0; i < pieces.getSize(); i++)
    {
        if (pieces[i]->y + pieces[i]->h < h - 1)
        {
            pieces[i]->updatePiece();
            return;
        }
    }
    createPiece();
}

void Board::updateFrame()
{
    clearFrame();
    // cout << pieces.getSize();
    for (int i = 0; i < pieces.getSize(); i++)
    {
        insertPiece(*pieces[i]);
    }
}

void Board::insertPiece(Piece piece)
{
    for (int i = 0; i < piece.w; i++)
    {
        for (int j = 0; j < piece.h; j++)
        {
            int index = piece.getIndex(w) + i * w + j;
            // index = (index < 0) ? 0 : index;
            frameArray[index] = piece.shapeArr[i * piece.w + j];
        }
    }
}

void Board::rotateCurrentPiece(int r)
{
    currentPiece->rotatePiece(r);
}

void Board::moveCurrentPiece(int dir)
{
    currentPiece->moveTo(currentPiece->x + dir, currentPiece->y);
}