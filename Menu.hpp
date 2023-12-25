#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Game.hpp"

class Menu
{

public:
    Menu();

    void displayMenu();        // Dısplay the buttons
    void handleInput(char ch); // Handles the give input accordingly
    void executeButton();      // executes the curButtonIndex buttons function
    void printFile(std::string fileName);

private:
    int curButtonIndex;
    int buttonNum;

    bool play; // if true, proceed to the game
    bool quit; // if true, quit the game

    friend class Game;
};