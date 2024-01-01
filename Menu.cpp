#include "Menu.hpp"

Menu::Menu(std::string *buttonArr, int arrSize) : curButtonIndex(0), buttonNum(arrSize), play(0), quit(false), buttons(buttonArr), restart(false) {}

void Menu::displayMenu()
{
    for (int i = 0; i < buttonNum; i++)
    {
        if (i == curButtonIndex)
        {
            std::cout << "\033[1;31m" << buttons[i] << "\033[0m" << std::endl;
            continue;
        }
        std::cout << buttons[i] << std::endl;
    }
}

void Menu::handleInput(char ch, std::function<void(Menu *)> executeButton)
{
    if (std::tolower(ch) == 's')
    {
        curButtonIndex = (curButtonIndex + 1) % buttonNum;
    }
    else if (std::tolower(ch) == 'w')
    {
        curButtonIndex = (curButtonIndex + buttonNum - 1) % buttonNum;
    }
    else if (std::tolower(ch) == '\n')
    {
        executeButton(this);
    }
}

void Menu::executeButtonMain(Menu *menu)
{
    switch (menu->curButtonIndex)
    {
    case 0: // start game
        menu->play = true;
        break;
    case 1: // change theme
        break;
    case 2: // Add piece
        break;
    case 3: // How to play?
        menu->printFile("how_to_play");
        break;
    case 4: // quit
        menu->play = true;
        menu->quit = true;
        break;

    default:
        break;
    };
}

void Menu::executeButtonGameOver(Menu *menu)
{
    switch (menu->curButtonIndex)
    {
    case 0: // Restart the game
        menu->play = true;
        menu->quit = false;
        menu->restart = true;
        break;

    case 1: // quit
        menu->play = true;
        menu->quit = true;
        return;
    }
    return;
}

void Menu::printFile(std::string fileName)
{
    system(CLEARCOMMAND);
    std::fstream newfile;
    newfile.open(fileName + ".txt", std::ios::in);
    while (Game::takeInput() != '\n')
    {
        if (newfile.is_open())
        {
            std::string tp;
            while (getline(newfile, tp))
            {
                cout << tp << "\n";
            }
        }
    }
    newfile.close();
}
