#include "Game.hpp"

Game::Game(int sleepTime) : sleepTime(sleepTime)
{
    Board board;
}

void Game::run()
{

    board.createPiece();

    while (true)
    {

        board.updateBoard();
        board.renderFrame();

        sleep(sleepTime);
        system(CLEARCOMMAND);
    }
}
