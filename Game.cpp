#include "Game.hpp"

Game::Game(int sleepTime) : sleepTime(sleepTime)
{
    Board board;
    gameSpeed = 500 / sleepTime;
}

void Game::run()
{

    // Set terminal to non-blocking mode (This is required since we dont want to press Enter)
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    board.createPiece();

    int frameCount = 0;
    char ch = EOF;
    // int speed = 17;

    while (true)
    {

        gameSpeed = 500 / sleepTime;
        ch = takeInput();
        handleInput(ch);
        frameCount = (frameCount + 1) % gameSpeed;

        board.updateFrame();
        if (frameCount == 0)
        {
            // Moves the piece downwards. Maybe change the function name
            board.updateCurrentPiece();
            board.checkLineComplete();
        }
        board.renderFrame();

        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        system(CLEARCOMMAND);
    }

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
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
        gameSpeed /= 7;
}
