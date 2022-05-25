#include "Grid.h"

#include <iostream>
#include <cstring>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

Grid::Grid(int n, int b) : grid(n*n), s(n*n), len(n), bombNum(b) {
    if(bombNum > len*len) bombNum = len*len;
    std::iota(s.begin(), s.end(), 0);
}

void Grid::printBombs() {
    std::cout << "    ";
    for(unsigned i = 0; i < len; i++) {
        std::cout << std::setw(3) << i;
    }
    std::cout << '\n';
    std::cout << "    ";
    for(unsigned i = 0; i < len; i++) {
        std::cout << "---";
    }
    std::cout << '\n';
    for(index i = 0; i < len; i++) {
        std::cout << std::setw(3) << i << "|";
        for(index j = 0; j < len; j++) {
            index pos = i*len+j;
            if(grid[pos].isBomb) {
                std::cout << std::setw(3) << "X";
            } else if(grid[pos].isChecked) {
               std::cout << std::setw(3) << grid[pos].number;
            } else std::cout << std::setw(3) << "-";
        }
        std::cout << '\n';
    }
}

void Grid::generateGrid() {
    clearGrid();
    shuffle(s.begin(),
        s.end(),
        std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
    for(index i = 0; i < bombNum; i++) {
        index randPos = s[i];
        grid[randPos].isBomb = true;
        index randRow = randPos/len;
        index randCol = randPos%len;
        if(randRow > 0) {
            ++grid[randPos-len].number;
            if(randCol > 0)
                ++grid[randPos-len-1].number;
            if(randCol < len-1)
                ++grid[randPos-len+1].number;
        }
        if(randRow < len-1) {
            ++grid[randPos+len].number;
            if(randCol > 0)
                ++grid[randPos+len-1].number;
            if(randCol < len-1)
                ++grid[randPos+len+1].number;
        }
        if(randCol > 0)
            ++grid[randPos-1].number;
        if(randCol < len-1)
            ++grid[randPos+1].number;
    }
}

void Grid::clearGrid() {
    for(index i = 0; i < len*len; i++) {
        grid[i].number = 0;
        grid[i].isBomb = grid[i].isChecked = grid[i].isMarked = false;
    }
}
