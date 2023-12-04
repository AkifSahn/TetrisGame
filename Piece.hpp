#include <time.h>
#include <stdlib.h>
#define NUMOFPIECE 10

enum pieceType
{
    plus = 1,
    ssquare = 2,
    corner = 3,
    tower = 4,
    zigzag = 5,
    u = 6,
    step = 7,
    arrow = 8,
    dzigzag = 9,
    pyramid = 10,
};

struct position
{
    int x;
    int y;
};

class Piece
{
public:
    Piece(); // Create a piece instance with random pieceType

    bool rotate(int); // -1 to counter-clockwise, +1 to clockwise

private:
    pieceType shape;
    int rotation; // 0 default, + rotates right, - rotates left
    position pos;
};