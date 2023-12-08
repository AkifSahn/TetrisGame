#include <time.h>
#include <stdlib.h>
#include <vector>

using std::vector;

class Piece
{
public:
    // Create a piece instance with random pieceType
    Piece();
    // Get a key of a piece and returns the according char.
    static char returnPiece(int);

private:
    vector<int> shapeArr; // A 1D array simulating an 3x3 2D array.
    // int rotation;         // 0 default, + rotates right, - rotates left
    int w, h; // Shape of the simulated 2D array
    int x, y; // Positions(representing the index in the current frame).
};