#pragma once

#ifdef _WIN32
#include <Windows.h>
#define CLEARCOMMAND "cls"
#else
#include <unistd.h>
#define CLEARCOMMAND "clear"
#endif

#include <iostream>

#include <chrono>
#include <thread>
#include <future>

#include <termio.h>
#include <fcntl.h>

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

private:
    Board board;
    int sleepTime; // wait time in seconds between each frame.
};