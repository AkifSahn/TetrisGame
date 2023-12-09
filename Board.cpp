#include "Board.hpp"

Board::Board() : w(8), h(8)
{
    // an empty frame
    frameArray = new int[w * h];
    for (int i = 0; i < w * h; i++)
    {
        frameArray[i] = 0;
    }
}

Piece Board::createPiece()
{
    Piece p;
    pieces.push_back(p);

    return p;
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

    for (int i = 0; i < w * h; i++)
    {
        frameArray[i] = 0;
    }

    for (int i = 0; i < pieces.size(); i++)
    {
        // updating the piece coordinates updating the frameArray accordingly
        pieces[i].updatePiece();
        insertPiece(pieces[i]);
    }
}

void Board::insertPiece(Piece piece)
{
    /*
        int j = 0;
        for (int i = piece.getIndex(); i <= piece.getIndex() + 9; i++, j++)
        {
            frameArray[i] = piece.getShape()[j];
        }
     */
    for (int i = 0; i < piece.getW(); i++)
    {
        for (int j = 0; j < piece.getH(); j++)
        {
            int index = piece.getIndex(w) + i * w + j;
            frameArray[index] = piece.getShape()[i * piece.getW() + j];
        }
    }
}
