#pragma once

#ifdef _WIN32
#include <Windows.h>
#define CLEARCOMMAND "cls"
#else
#include <unistd.h>
#define CLEARCOMMAND "clear"
#endif

#include <iostream>

#include <termio.h>
#include <fcntl.h>

#include <thread>
#include <chrono>

#include "Piece.hpp"
#include "Board.hpp"

class Game
{
public:
    Game(int);

    // run the game
    void run();

    // returns the pressed key;
    char takeInput();

    void handleInput(char);

private:
    Board board;
    int sleepTime; // wait time in ms between each frame.
    int gameSpeed;
};