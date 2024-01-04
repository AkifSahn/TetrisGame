#include "Game.hpp"
int main()
{

    system("cat standardPieces.txt > pieces.txt");

    Game game(30);

    game.runMenu();
    game.run();

    system("cat standardPieces.txt > pieces.txt");

    game.endNonBlocking();

    return 0;
}