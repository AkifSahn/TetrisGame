#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Game.hpp"

class Menu
{

public:
    Menu(std::string *buttonArr, int arrSize);

    void displayMenu();                                                   // Dısplay the buttons
    void handleInput(char ch, std::function<void(Menu *)> executeButton); // Handles the given input according to the executeButton function
    static void executeButtonMain(Menu *menu);
    static void printFile(std::string fileName);

private:
    int curButtonIndex;

    std::string *buttons;
    int buttonNum;

    bool play; // if true, proceed to the game
    bool quit; // if true, quit the game
    bool addPiece;

    friend class Game;
};