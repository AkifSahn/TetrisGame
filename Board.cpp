#include "Board.hpp"
#define PIECENUMBER 7

Board::Board() : infoWidth(10), w(30), h(20), holdingPiece(nullptr), nextPiece(nullptr)
{
    // empty frame, with boundaries
    currentPiece = nullptr;
    frameArray = new int[w * h];
    prevFrameArray = new int[w * h];

    clearFrame();
    copyFrameArray(frameArray, prevFrameArray);
}
Board::~Board()
{
    clearFrame();
    nextPiece = nullptr;
    currentPiece = nullptr;
    delete currentPiece;
    delete[] frameArray;
    delete[] prevFrameArray;
}

void Board::clearFrame()
{
    int index;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            index = i * w + j;

            if (j == 0 || j == w - (infoWidth + 1) || i == h - 1)
            {
                frameArray[index] = 30;
                continue;
            }

            frameArray[index] = 0; // i = y*w + x
        }
    }
}

Piece Board::createPiece()
{

    currentPiece = nullptr;

    if (nextPiece == nullptr)
    {
        // currentPiece = new Piece(7, 0);
        nextPiece = new Piece(7, 0, PIECENUMBER);
    }

    currentPiece = nextPiece;
    currentPiece->moveTo(7, 0);
    pieces.pushBack(currentPiece);

    nextPiece = nullptr;
    nextPiece = new Piece(w - 8, 6, PIECENUMBER);

    return *currentPiece;
}

void Board::updateFrame()
{

    copyFrameArray(prevFrameArray, frameArray);
    insertPiece(*currentPiece, frameArray);
    insertPiece(*nextPiece, frameArray);
    displayHeldPiece();
}

void Board::updateCurrentPiece()
{
    if (!detectCollisionVertical(*currentPiece))
    {

        currentPiece->updatePiece();
        return;
    }
    insertPiece(*currentPiece, prevFrameArray);
    createPiece();
}

void Board::renderFrame()
{
    int color;
    int index;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            index = i * w + j;
            color = frameArray[index];

            cout << "\033[40;" + std::to_string(color) + "m" << Piece::returnPiece(frameArray[index]) << "\033[0m";
        }
        cout << endl;
    }
}

void Board::insertPiece(Piece piece, int *&dest)
{
    for (int i = 0; i < piece.w; i++)
    {
        for (int j = 0; j < piece.h; j++)
        {
            int index = piece.getIndex(w) + i * w + j;

            if (piece.shapeArr[i * piece.w + j] != 0)
            {
                dest[index] = piece.shapeArr[i * piece.w + j];
            }
        }
    }
}

bool Board::isRotateable(Piece &piece, int rotation)
{
    switch (rotation)
    {
    case 90:
        return !detectCollisionHorizontalRight(piece);
        break;

    case 270:
        return !detectCollisionHorizontalLeft(piece);
        break;
    default:
        return true;
    }
}

void Board::rotateCurrentPiece(int r)
{
    if (isRotateable(*currentPiece, r))
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
    for (int i = 0; i < piece.h; i++)
    {
        for (int j = 0; j < piece.w; j++)
        {
            if (pieceShape[i * piece.w + j] == 0)
            {
                continue;
            }

            if (frameArray[index + i * w + j - 1] != 0 && (j == 0 || pieceShape[i * piece.w + j - 1] == 0))
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
    bool flag;
    for (int i = 0; i < piece.h; i++)
    {
        for (int j = 0; j < piece.w; j++)
        {
            if ((pieceShape[i * piece.w + j] == 0))
            {
                continue;
            }

            // Down check
            if (frameArray[index + i * w + j + w] != 0 && (i == piece.h - 1 || pieceShape[i * piece.w + j + piece.w] == 0))
            {
                flag = true;
                continue;
            }
        }
    }
    return flag;
}

bool Board::isGameOver()
{
    for (int i = 0; i < pieces.getSize(); i++)
    {
        if (pieces[i] == currentPiece)
        {
            continue;
        }

        if (pieces[i]->y <= 0 && pieces[i]->x < w - infoWidth)
        {
            return true;
        }
    }
    return false;
}

void Board::checkLineComplete(int &score)
{
    int count;
    int index;
    for (int i = h - 2; i >= 0; i--)
    {
        count = 0;
        for (int j = w - (infoWidth + 2); j >= 1; j--)
        {
            index = i * w + j;
            if (prevFrameArray[index] == 0)
                continue;

            count++;
        }

        if (count == w - (infoWidth + 2))
        {
            // delete the row
            for (int j = w - (infoWidth + 2); j >= 1; j--)
            {
                index = i * w + j;
                prevFrameArray[index] = 0;
            }
            // slide down the frame
            slideDownFrame(i);
            score += 10;
        }
    }
}

void Board::slideDownFrame(int startIndex)
{
    int index;
    for (int i = startIndex - 1; i >= 0; i--)
    {
        for (int j = 1; j <= w - (infoWidth + 2); j++)
        {
            index = i * w + j;
            prevFrameArray[index + w] = prevFrameArray[index];
            prevFrameArray[index] = 0;
        }
    }
}

void Board::copyFrameArray(int *&source, int *&dest)
{
    for (int i = 0; i < w * h; i++)
    {
        dest[i] = source[i];
    }
}

void Board::holdCurrentPiece()
{
    if (holdingPiece != nullptr)
    {
        Piece tempPiece = *holdingPiece;
        *holdingPiece = *currentPiece;
        *currentPiece = tempPiece;
        currentPiece->moveTo(holdingPiece->x, holdingPiece->y);
    }
    else
    {
        holdingPiece = currentPiece;
        createPiece();
        currentPiece->moveTo(holdingPiece->x, holdingPiece->y);
    }
}

void Board::displayHeldPiece()
{
    if (holdingPiece != nullptr)
    {
        holdingPiece->moveTo(w - 8, 0);
        insertPiece(*holdingPiece, frameArray);
    }
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