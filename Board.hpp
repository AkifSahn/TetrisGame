#pragma once

#include <iostream>
#include <vector>
#include "Piece.hpp"
#include "SimpleVector.hpp"

using std::cout;
using std::endl;
using std::vector;
class Board
{
public:
    Board();
    // Create a piece and append to the pieces.
    Piece createPiece();
    // Takes the frame, width, height of the frame.
    void renderFrame();

    void updateBoard();
    void insertPiece(Piece);

    void rotateCurrentPiece(int);
    // 1 moves right -1 moves left
    void moveCurrentPiece(int);

private:
    int w, h;
    int *frameArray;
    SimpleVector<Piece *> pieces;

    Piece *currentPiece;
};
