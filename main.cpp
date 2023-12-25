#include "Game.hpp"

struct termios oldt, newt;
int oldf;
void startNonBlocking()
{
    // Set terminal to non-blocking mode (This is required since we dont want to press Enter)
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
}

void endNonBlocking()
{
    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
}

int main()
{

    startNonBlocking();

    Game game(30);
    game.runMenu();
    game.run();

    endNonBlocking();

    return 0;
}