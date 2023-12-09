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
        board.renderFrame();
        board.updateBoard();

        sleep(sleepTime);
        system(CLEARCOMMAND);
    }
}