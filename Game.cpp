#include "Game.hpp"

Game::Game(int sleepTime) : sleepTime(sleepTime), score(0), isPlaying(true), restartFlag(true)
{
    Board board;
    gameSpeed = 500 / sleepTime;
}

bool Game::isRestart()
{
    return restartFlag;
}

void Game::runMenu()
{

    std::string buttons[5] = {"Start game", "Change theme (To be added)", "Add piece (To be added)", "How to play?", "Quit"};

    Menu menu(buttons, 5);

    std::function<void(Menu *)> execFunc = Menu::executeButtonMain;

    while (!menu.play)
    {
        menu.displayMenu();
        menu.handleInput(Game::takeInput(), execFunc);
        isPlaying = !menu.quit;
        std::this_thread::sleep_for(std::chrono::milliseconds(35));
        system(CLEARCOMMAND);
    }
}

void Game::gameOverMenu()
{
    std::string buttons[2] = {"Restart the game", "Quit"};

    Menu menu(buttons, 2);

    std::function<void(Menu *)> execFunc = Menu::executeButtonGameOver;

    while (!menu.play)
    {
        menu.displayMenu();
        menu.handleInput(Game::takeInput(), execFunc);
        isPlaying = !menu.quit;
        restartFlag = menu.restart;
        std::this_thread::sleep_for(std::chrono::milliseconds(35));
        system(CLEARCOMMAND);
    }
}

void Game::restart()
{
    board.~Board();
    board = Board();
    score = 0;
    isPlaying = true;
    restartFlag = true;
    gameSpeed = 500 / sleepTime;
}

void Game::setRestart(bool x)
{
    restartFlag = x;
}

void Game::run()
{

    board.createPiece();

    int frameCount = 0;
    char ch = EOF;

    int highscore = readHighScore();

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
            board.updateCurrentPiece();
            board.checkLineComplete(score);
            isPlaying = !board.isGameOver();
        }
        board.renderFrame();

        if (score > highscore)
        {

            highscore = score;
        }

        cout << "Score: " << score << endl;
        cout << "High score: " << highscore << endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        system(CLEARCOMMAND);
    }
    if (score > readHighScore())
    {
        updateHighScore(score);
    }
}

void Game::updateHighScore(int score)
{

    std::ofstream file;
    file.open("highscore.txt");
    file << score << std::endl;
    file.close();
}

int Game::readHighScore()
{
    std::ifstream file;
    file.open("highscore.txt");
    std::string score;

    getline(file, score);
    return std::stoi(score);
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
