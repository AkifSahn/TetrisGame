#include "Menu.hpp"

std::string buttons[5] = {"Start game", "Change theme (To be added)", "Add piece (To be added)", "How to play?", "Quit"};

Menu::Menu() : curButtonIndex(0), buttonNum(5), play(0), quit(false) {}

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

void Menu::handleInput(char ch)
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
        executeButton();
    }
}

void Menu::executeButton()
{
    switch (curButtonIndex)
    {
    case 0: // start game
        play = true;
        break;
    case 1: // change theme
        break;
    case 2: // Add piece
        break;
    case 3: // How to play?
        printFile("how_to_play");
        break;
    case 4: // quit
        play = true;
        quit = true;
        break;

    default:
        break;
    };
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
