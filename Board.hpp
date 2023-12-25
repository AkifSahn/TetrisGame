#pragma once

#include <iostream>
#include <string>
#include <random>
#include <time.h>

#include "Piece.hpp"
#include "SimpleVector.hpp"

using std::cout;
using std::endl;

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

    void updateCurrentPiece();
    // updates the frame by inserting the pieces into frame(calls insertPiece)
    void updateFrame();
    // inserting a piece to frame
    void insertPiece(Piece, int *&dest);

    bool isRotateable(Piece &piece, int rotation);
    void rotateCurrentPiece(int);
    // 1 moves right -1 moves left
    void moveCurrentPiece(int dir);

    // detecting collisions
    bool detectCollisionVertical(Piece);
    bool detectCollisionHorizontalRight(Piece);
    bool detectCollisionHorizontalLeft(Piece);

    void checkLineComplete(int &score);  // takes in score to update
    void slideDownFrame(int startIndex); // slides the rows above startIndex
    void copyFrameArray(int *&source, int *&dest);

    void holdCurrentPiece();
    void displayHeldPiece();

    void printFrameArray();

private:
    int w, h;
    int infoWidth;
    int *frameArray;
    int *prevFrameArray;
    SimpleVector<Piece *> pieces;

    Piece *currentPiece;
    Piece *holdingPiece;
    Piece *nextPiece;

    // friend class Game;
};
