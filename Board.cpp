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
                frameArray[index] = 2;
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
    if (!detectCollisionVertical(*currentPiece))
    {

        currentPiece->updatePiece();
        return;
    }
    createPiece();
}

void Board::updateFrame()
{
    clearFrame();
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
            frameArray[index] = (piece.shapeArr[i * piece.w + j]) ? (piece.shapeArr[i * piece.w + j] != 0) : frameArray[index];
        }
    }
}

void Board::rotateCurrentPiece(int r)
{
    currentPiece->rotatePiece(r);
}

void Board::moveCurrentPiece(int dir)
{
    int destX = currentPiece->x + dir;
    int destY = currentPiece->y;

    switch (dir)
    {
    case -1: // moving left
        if (!detectCollisionHorizontalLeft(*currentPiece))
        {
            currentPiece->moveTo(destX, destY);
        }
        break;

    case 1: // moving right
        if (!detectCollisionHorizontalRight(*currentPiece))
        {
            currentPiece->moveTo(destX, destY);
        }
        break;
    }
}

bool Board::detectCollisionHorizontalRight(Piece piece)
{
    auto pieceShape = piece.shapeArr;

    int index = piece.getIndex(w); // top left coordinate of the piece
    for (int i = 0; i < piece.h; i++)
    {
        for (int j = 0; j < piece.w; j++)
        {
            if (pieceShape[i * piece.w + j] == 0)
                continue;

            if ((frameArray[index + i * w + j + 1] != 0) && (j == piece.w - 1 || pieceShape[i * piece.w + j + 1] == 0))
            {
                return true;
            }
        }
    }
    return false;
}

bool Board::detectCollisionHorizontalLeft(Piece piece)
{
    auto pieceShape = piece.shapeArr;

    int index = piece.getIndex(w); // top left coordinate of the piece
    int diff;
    for (int i = 0; i < piece.h; i++)
    {
        for (int j = 0; j < piece.w; j++)
        {
            diff = i * w + j;
            if (pieceShape[i * piece.w + j] == 0)
            {
                continue;
            }

            if (frameArray[index + diff - 1] != 0 && (j == 0 || pieceShape[i * piece.w + j - 1] == 0))
            {
                return true;
            }
        }
    }
    return false;
}

bool Board::detectCollisionVertical(Piece piece)
{

    auto pieceShape = piece.shapeArr;

    int index = piece.getIndex(w);
    int diff;
    bool flag;
    for (int i = 0; i < piece.h; i++)
    {
        for (int j = 0; j < piece.w; j++)
        {
            diff = i * w + j;
            if ((pieceShape[i * piece.w + j] == 0))
            {
                continue;
            }

            // Down check
            if (frameArray[index + diff + w] != 0 && (pieceShape[i * piece.w + j + piece.w] == 0))
            {
                flag = true;
                continue;
            }
        }
    }
    return flag;
}

void Board::checkLineCompete()
{
    return;
}

void Board::printFrameArray()
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            std::cout << frameArray[i * w + j] << " ";
        }
        std::cout << std::endl;
    }
}