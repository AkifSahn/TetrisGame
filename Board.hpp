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
    ~Board();

    // Clears the frame with bpundaries
    void clearFrame();

    // Create a piece and append to the pieces.
    Piece createPiece();
    // Takes the frame, width, height of the frame.
    void renderFrame();

    void updateBoard();
    // updates the frame by inserting the pieces into frame
    void updateFrame();
    // inserting a piece to frame
    void insertPiece(Piece);

    void rotateCurrentPiece(int);
    // 1 moves right -1 moves left
    void moveCurrentPiece(int);

    // detects if there is another piece at the left, right or bottom of the given piece; if there is, returns true.
    bool detectCollisionVertical(Piece);
    bool detectCollisionHorizontalRight(Piece);
    bool detectCollisionHorizontalLeft(Piece);

    void checkLineCompete();

    void printFrameArray();

private:
    int w, h;
    int *frameArray;
    SimpleVector<Piece *> pieces;

    Piece *currentPiece;
};
