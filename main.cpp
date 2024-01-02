#include "Game.hpp"
int main()
{

    system("cat standardPieces.txt > pieces.txt");

    Game game(30);
    while (game.isRestart())
    {
        game.setRestart(false);

        game.runMenu();

        game.run();
        game.gameOverMenu();
        if (game.isRestart())
        {
            game.restart();
        }
    }

    game.endNonBlocking();

    return 0;
}