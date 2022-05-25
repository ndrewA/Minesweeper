#ifndef GAME_H
#define GAME_H

#include "Grid.h"

#include <string>

class Game
{
    private:
        Grid grid;
        int len;
        int foundNum;
        int checkedNum;

    public:
        Game(int n, int b) : grid(n, b), len(n), foundNum(0), checkedNum(0) {}
        ~Game() {}
        void printChecked();
        void playGame();

    private:
        void getInput(std::string& prefix, int& row, int& col);
        void clearSpace(int n, int m);
};

#endif // GAME_H
