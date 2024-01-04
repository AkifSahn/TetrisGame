#include "Game.hpp"

Game::Game(int sleepTime) : sleepTime(sleepTime), score(0), isPlaying(true)
{
    Board board;
    startNonBlocking();
    gameSpeed = 500 / sleepTime;
}

void Game::startNonBlocking()
{
    // Set terminal to non-blocking mode (This is required since we dont want to press Enter)
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
}

void Game::endNonBlocking()
{
    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
}

void Game::run()
{

    Piece::readPieceFile(board.numOfPieces);

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
            pauseMenu();
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

        cout << "\033[1;32mScore: " << score << "\033[0m" << endl;
        cout << "\033[1;31mHigh score: " << highscore << "\033[0m" << endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        system(CLEARCOMMAND);
    }
    if (score > readHighScore())
    {
        updateHighScore(score);
    }
}

void Game::runMenu()
{

    std::string buttons[5] = {"Start game", "Change theme", "Add piece", "How to play?", "Quit"};

    Menu menu(buttons, 5);

    std::function<void(Menu *)> execFunc = Menu::executeButtonMain;

    while (!menu.play)
    {
        menu.displayMenu();
        menu.handleInput(Game::takeInput(), execFunc);
        isPlaying = !menu.quit;
        if (board.numOfPieces >= 10)
        {
            buttons[2] = "Add piece | Can't add more piece";
        }
        else if (menu.addPiece)
        {
            endNonBlocking();
            addPieceMenu();
            startNonBlocking();
            menu.addPiece = false;
        }
        if (menu.changeTheme)
        {
            changeThemeMenu();
            menu.changeTheme = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(35));
        system(CLEARCOMMAND);
    }
}

void Game::pauseMenu()
{
    std::string buttons[3] = {"Continue", "Change theme", "Quit"};
    Menu menu(buttons, 3);
    std::function<void(Menu *)> execFunc = Menu::executeButtonPause;

    while (!menu.play)
    {
        menu.displayMenu();
        menu.handleInput(Game::takeInput(), execFunc);

        isPlaying = !menu.quit;
        if (menu.changeTheme)
        {
            changeThemeMenu();
            menu.changeTheme = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(35));
        system(CLEARCOMMAND);
    }
}

void Game::addPieceMenu()
{
    system(CLEARCOMMAND);

    // int piece[16] = {0};
    int index = 0;
    std::string piece = "\n{";
    std::string row;
    for (int i = 0; i < 4; i++)
    {

        std::cout << "Enter row #" << i + 1 << ": ";
        std::cin >> row;
        if (row == "q" || row == "Q")
        {
            return;
        }

        piece += row + ",";
    }
    piece += "}";

    addToPieces(piece);
}

void Game::changeThemeMenu()
{
    std::string buttons[4] = {"X theme", "# Theme", "O theme(default)", "Back"};
    Menu menu(buttons, 4);

    std::function<void(Menu *)> execFunc = Menu::executeButtonTheme;

    while (!menu.play)
    {
        menu.displayMenu();
        menu.handleInput(Game::takeInput(), execFunc);
        board.blockChar = menu.themePiece;

        std::this_thread::sleep_for(std::chrono::milliseconds(35));
        system(CLEARCOMMAND);
    }
}

void Game::addToPieces(std::string piece)
{
    std::ofstream file;
    file.open("pieces.txt", std::ios_base::app); // append instead of overwrite
    file << piece;
    board.numOfPieces++;
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
