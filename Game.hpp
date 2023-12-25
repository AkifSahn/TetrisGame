#pragma once

#include <unistd.h>
#define CLEARCOMMAND "clear"

#include <iostream>

#include <termio.h>
#include <fcntl.h>

#include <thread>
#include <chrono>

#include "Piece.hpp"
#include "Board.hpp"
#include "Menu.hpp"

class Game
{
public:
    Game(int);

    // display the main menu
    void runMenu();

    // run the game
    void run();

    // returns the pressed key;
    static char takeInput();

    void handleInput(char);

private:
    Board board;
    int sleepTime; // wait time in ms between each frame.
    int gameSpeed;
    int score;

    bool isPlaying;
};