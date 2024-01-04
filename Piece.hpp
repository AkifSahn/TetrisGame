#pragma once
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include "SimpleVector.hpp"

class Piece
{
public:
    // Create a piece instance with random pieceType
    Piece(int x, int y, int pieceNumber);
    ~Piece();
    // Get a key of a piece and returns the according char.
    // Rotate the piece r degree. 0 rotates to default rotation.
    void rotatePiece(int);

    void moveTo(int, int);
    void updatePiece();

    int getIndex(int boardWidth);

    static void readPieceFile(int numOfPiece);

    void printShape();

    friend class Board;

private:
    int *shapeArr; // A 1D array simulating a 4x4 matrix.
    int rotation;  // 0, 90, 270
    int w, h;      // Shape of the simulated matrix
    int x, y;      // Positions(representing the index in the current frame).
    int stdIndex;  // StandardPieces index of the piece

    // int numOfPiece;
    int color; // 31=red, 32=green, 34=blue
};