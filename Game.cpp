#include "Game.hpp"

Game::Game(int sleepTime) : sleepTime(sleepTime)
{
    Board board;
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

    char ch = EOF;

    while (true)
    {

        ch = takeInput();
        if (ch == 'e')
        {
            board.rotateCurrentPiece(90);
        }
        if (ch == 'q')
        {
            break;
        }

        board.updateBoard();
        board.renderFrame();

        sleep(sleepTime);
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
