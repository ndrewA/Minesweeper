#include "Game.h"

#include <queue>
#include <cstddef>
#include <iomanip>
#include <cstring>
#include <iostream>

void Game::printChecked() {
    std::cout << "    ";
    for(int i = 0; i < len; i++) {
        std::cout << std::setw(3) << i;
    }
    std::cout << '\n';
    std::cout << "    ";
    for(int i = 0; i < len; i++) {
        std::cout << "---";
    }
    std::cout << '\n';
    for(int i = 0; i < len; i++) {
        std::cout << std::setw(3) << i << "|";
        for(int j = 0; j < len; j++) {
            if(grid.isChecked(i, j)) {
                std::cout << std::setw(3) << grid.getNum(i, j);
            } else if(grid.isFlagged(i, j)) {
                std::cout << std::setw(3) << "*";
            } else std::cout << std::setw(3) << "-";
        }
        std::cout << '\n';
    }
}

void Game::playGame() {
    grid.generateGrid();
    int row, col;
    bool firstAttempt = true;
    while(true) {
        printChecked();
        std::string prefix = "";
        getInput(prefix, row, col);
        if((firstAttempt && (prefix == "get")) && (len*len > grid.getBombNum())) {
            firstAttempt = false;
            while(grid.isBomb(row, col))
                grid.generateGrid();
        }
        if((prefix == "flag") && (!grid.isChecked(row, col))) {
            if(grid.isBomb(row, col)) ++foundNum;
            grid.flagCell(row, col, true);
        } else if((prefix == "unflag") && grid.isFlagged(row, col)) {
            if(grid.isBomb(row, col)) --foundNum;
            grid.flagCell(row, col, false);
        } else if((prefix == "get") && (!grid.isFlagged(row, col))){
            if(grid.isBomb(row, col)) {
                grid.printBombs();
                std::cout << "YOU HAVE LOST\n";
                break;
            }
            clearSpace(row, col);
        }
        if((grid.getBombNum() == foundNum) && (checkedNum == len*len - grid.getBombNum())) {
            grid.printBombs();
            std::cout << "YOU HAVE WON\n";
            break;
        }
    }
}

void Game::getInput(std::string& prefix, int& row, int& col) {
    prefix = "";
    while((prefix != "flag" && prefix != "unflag") && prefix != "get")
        std::cin >> prefix;
    std::string ph = "placeholder";
    while((ph.find_first_not_of("0123456789") != std::string::npos) || (ph.size() > len/10+1))
        std::cin >> ph;
    row = std::stoi(ph);
    ph = "placeholder";
    while((ph.find_first_not_of("0123456789") != std::string::npos) || (ph.size() > len/10+1))
        std::cin >> ph;
    col = std::stoi(ph);
    if((row >= len || row < 0) || (col >= len) || ( col < 0)) getInput(prefix, row, col);
}

void Game::clearSpace(int row, int col) {
    if(grid.isChecked(row, col) || grid.isFlagged(row, col)) return;
    ++checkedNum;
    std::queue<std::pair<int, int>> q;
    grid.checkCell(row, col);
    if(grid.getNum(row, col) == 0) q.emplace(row, col);
    while(!q.empty()) {
        row = q.front().first;
        col = q.front().second;
        grid.checkCell(row, col);
        if((row < len-1) && (!grid.isChecked(row+1, col))) {
            if(grid.getNum(row+1, col) == 0)
                q.emplace(row+1, col);
            grid.checkCell(row+1, col);
            ++checkedNum;
        }

        if((row < len-1) && (col < len-1) && (!grid.isChecked(row+1, col+1))) {
            if(grid.getNum(row+1, col+1) == 0)
                q.emplace(row+1, col+1);
            grid.checkCell(row+1, col+1);
            ++checkedNum;
        }

        if((row < len-1) && (col > 0)  && (!grid.isChecked(row+1, col-1))) {
            if(grid.getNum(row+1, col-1) == 0)
                q.emplace(row+1, col-1);
            grid.checkCell(row+1, col-1);
            ++checkedNum;
        }

        if((col < len-1) && (!grid.isChecked(row, col+1))) {
            if(grid.getNum(row, col+1) == 0)
                q.emplace(row, col+1);
            grid.checkCell(row, col+1);
            ++checkedNum;
        }

        if((row > 0) && (!grid.isChecked(row-1, col))) {
            if(grid.getNum(row-1, col) == 0)
                q.emplace(row-1, col);
            grid.checkCell(row-1, col);
            ++checkedNum;
        }

        if((row > 0) && (col < len-1) && (!grid.isChecked(row-1, col+1))) {
            if(grid.getNum(row-1, col+1) == 0)
                q.emplace(row-1, col+1);
            grid.checkCell(row-1, col+1);
            ++checkedNum;
        }

        if((row > 0) && (col > 0)  && (!grid.isChecked(row-1, col-1))) {
            if(grid.getNum(row-1, col-1) == 0)
                q.emplace(row-1, col-1);
            grid.checkCell(row-1, col-1);
            ++checkedNum;
        }

        if((col > 0)  && (!grid.isChecked(row, col-1))) {
            if(grid.getNum(row, col-1) == 0)
                q.emplace(row, col-1);
            grid.checkCell(row, col-1);
            ++checkedNum;
        }
        q.pop();
    }
}
