#ifndef GRID_H
#define GRID_H

#include <vector>

typedef unsigned index;

struct Cell
{
    bool isBomb;
    bool isMarked;
    bool isChecked;
    unsigned number;
    Cell() {
        isBomb = isMarked = isChecked = false;
        number = 0;
    }
};

class Grid
{
    private:
        std::vector<Cell> grid;
        std::vector<unsigned> s;
        unsigned len;
        unsigned bombNum;

    public:
        Grid(int n, int b);
        ~Grid() {}
        void printBombs();
        void generateGrid();
        void checkCell(index row, index col) {grid[getPos(row, col)].isChecked = true;}
        void flagCell(index row, index col, bool b) {grid[getPos(row, col)].isMarked = b;}
        unsigned getNum(index row, index col) {return grid[getPos(row, col)].number;}
        int getBombNum() {return bombNum;}
        bool isChecked(index row, index col) {return grid[getPos(row, col)].isChecked;}
        bool isFlagged(index row, index col) {return grid[getPos(row, col)].isMarked;}
        bool isBomb(index row, index col) {return grid[getPos(row, col)].isBomb;}

    private:
        void clearGrid();
        index getPos(index row, index col) {return row*len+col;}
};

#endif // GRID_H
