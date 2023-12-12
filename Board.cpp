#include "Board.hpp"

Board::Board() : w(20), h(20)
{
    // empty frame
    frameArray = new int[w * h];
    for (int i = 0; i < w * h; i++)
    {
        frameArray[i] = 0;
    }
}

Piece Board::createPiece()
{
    Piece p;
    currentPiece = &p;
    pieces.pushBack(&p);
    return p;
}

Board::~Board()
{
    delete currentPiece;
    delete[] frameArray;
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

    if (currentPiece->getY() + currentPiece->getH() < h)
    {
        currentPiece->updatePiece();
    }
}

void Board::updateFrame()
{
    // clearing the frame
    for (int i = 0; i <= w * h; i++)
    {
        frameArray[i] = 0;
    }

    for (int i = 0; i < pieces.getSize(); i++)
    {
        insertPiece(*pieces[i]);
    }
}

void Board::insertPiece(Piece piece)
{
    for (int i = 0; i < piece.getW(); i++)
    {
        for (int j = 0; j < piece.getH(); j++)
        {
            int index = piece.getIndex(w) + i * w + j;
            frameArray[index] = piece.getShape()[i * piece.getW() + j];
        }
    }
}

void Board::rotateCurrentPiece(int r)
{
    currentPiece->rotatePiece(r);
    // insertPiece(*currentPiece);
}

void Board::moveCurrentPiece(int dir)
{
    currentPiece->moveTo(currentPiece->getX() + dir, currentPiece->getY());
}