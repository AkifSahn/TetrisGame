#include <time.h>
#include <stdlib.h>
#include <random>

using std::vector;

int standardPieces[10][9] = {{0, 1, 0, 1, 1, 1, 0, 1, 0},  // plus
                             {1, 1, 0, 1, 1, 0, 0, 0, 0},  // square
                             {1, 0, 0, 1, 1, 0, 0, 0, 0},  // corner
                             {1, 0, 0, 1, 0, 0, 1, 0, 0},  // line
                             {0, 1, 1, 1, 1, 0, 0, 0, 0},  // zig-zag
                             {1, 0, 1, 1, 1, 1, 0, 0, 0},  // U piece
                             {1, 0, 0, 1, 1, 0, 0, 1, 0},  // step piece
                             {0, 1, 0, 1, 1, 1, 1, 0, 1},  // up arrow
                             {1, 0, 0, 1, 1, 1, 0, 0, 1},  // Double zig-zag
                             {0, 1, 0, 1, 1, 1, 0, 0, 0}}; // pyramid

class Piece
{
public:
    // Create a piece instance with random pieceType
    Piece();
    ~Piece();
    // Get a key of a piece and returns the according char.
    static char returnPiece(int);
    // Rotate the piece clockwise to the given r(degree). r can take 0, 90, 180, 270
    void rotatePiece(int r);

private:
    int *shapeArr; // A 1D array simulating an 3x3 2D array.
    int rotation;  // 0, 90, 180, 270
    int w, h;      // Shape of the simulated 2D array
    int x, y;      // Positions(representing the index in the current frame).
    int stdIndex;  // StandardPieces index of the piece
};