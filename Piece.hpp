#pragma once
#include <time.h>
#include <stdlib.h>

class Piece
{
public:
    // Create a piece instance with random pieceType
    Piece(int x, int y);
    ~Piece();
    // Get a key of a piece and returns the according char.
    static char returnPiece(int);
    // Rotate the piece r degree. 0 rotates to default rotation.
    void rotatePiece(int);

    void moveTo(int, int);
    void updatePiece();

    int getIndex(int);

    friend class Board;

private:
    int *shapeArr; // A 1D array simulating an 3x3 2D array.
    int rotation;  // 0, 90, 270
    int w, h;      // Shape of the simulated 2D array
    int x, y;      // Positions(representing the index in the current frame).
    int stdIndex;  // StandardPieces index of the piece
};