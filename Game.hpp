#pragma once

#include <unistd.h>
#define CLEARCOMMAND "clear"

#include <iostream>
#include <functional>

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

    bool isRestart();

    // display the main menu
    void runMenu();
    void gameOverMenu();

    void restart();
    void setRestart(bool);

    // run the game
    void run();

    // returns the pressed key;
    static char takeInput();

    static void updateHighScore(int score);
    static int readHighScore();

    void handleInput(char);

private:
    Board board;
    int sleepTime; // wait time in ms between each frame.
    int gameSpeed;
    int score;

    bool restartFlag;
    bool isPlaying;
};