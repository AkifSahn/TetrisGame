#pragma once

#include <iostream>
#include <vector>
#include "Piece.hpp"

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

private:
    int w, h;
    int *frameArray;
    vector<Piece> pieces;
};
