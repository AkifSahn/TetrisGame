#include "Game.hpp"

Game::Game(int sleepTime) : sleepTime(sleepTime), score(0), isPlaying(true)
{
    Board board;
    gameSpeed = 500 / sleepTime;
}

void Game::runMenu()
{
    Menu menu;
    while (!menu.play)
    {
        menu.displayMenu();
        menu.handleInput(Game::takeInput());
        isPlaying = !menu.quit;
        std::this_thread::sleep_for(std::chrono::milliseconds(35));
        system(CLEARCOMMAND);
    }
}

void Game::run()
{

    board.createPiece();

    int frameCount = 0;
    char ch = EOF;

    while (isPlaying)
    {

        gameSpeed = 500 / sleepTime;
        ch = takeInput();
        handleInput(ch);
        if (ch == 'c')
        {
            isPlaying = false;
        }

        frameCount = (frameCount + 1) % gameSpeed;

        board.updateFrame();
        if (frameCount == 0)
        {
            // Moves the piece downwards. Maybe change the function name
            board.updateCurrentPiece();
            board.checkLineComplete(score);
        }
        board.renderFrame();
        cout << "Score: " << score << endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        system(CLEARCOMMAND);
    }
}

char Game::takeInput()
{
    char ch;
    int n = read(STDIN_FILENO, &ch, 1);
    if (n > 0)
    {
        return ch;
    }

    return EOF;
}

void Game::handleInput(char ch)
{
    // ROTATING
    if (ch == 'e')
    {
        board.rotateCurrentPiece(90);
    }
    else if (ch == 'q')
    {
        board.rotateCurrentPiece(270);
    }

    // MOVING
    if (ch == 'a')
    {
        board.moveCurrentPiece(-1);
    }
    else if (ch == 'd')
    {
        board.moveCurrentPiece(1);
    }

    if (ch == 's')
        gameSpeed /= 10;

    // Holding piece
    if (ch == 'w')
    {
        board.holdCurrentPiece();
    }
}
