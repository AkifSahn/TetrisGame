#include "Menu.hpp"

Menu::Menu(std::string *buttonArr, int arrSize) : curButtonIndex(0), buttonNum(arrSize), play(0), quit(false), buttons(buttonArr), addPiece(false), changeTheme(false), themePiece('O'), adjustBoard(false) {}

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
        menu->changeTheme = true;
        break;
    case 2: // Add piece
        // menu->play = true;
        menu->addPiece = true;

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

void Menu::executeButtonTheme(Menu *menu)
{
    switch (menu->curButtonIndex)
    {
    case 0: // X
        menu->themePiece = 'X';
        menu->play = true;
        break;
    case 1: // #
        menu->themePiece = '#';
        menu->play = true;
        break;
    case 2: // O
        menu->themePiece = 'O';
        menu->play = true;
        break;
    case 3: // Back
        menu->play = true;

    default:
        menu->themePiece = 'O';
        break;
    }
}

void Menu::executeButtonPause(Menu *menu)
{
    switch (menu->curButtonIndex)
    {
    case 0: // continue
        menu->play = true;
        break;
    case 1: // change theme
        menu->changeTheme = true;
        break;
    case 2: // quit
        menu->play = true;
        menu->quit = true;
        break;

    default:
        break;
    }
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
