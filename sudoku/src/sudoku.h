#include <iostream>
#include <cstring>
//design taken from
//https://www.geeksforgeeks.org/sudoku-backtracking-7/
class Sudoku {
private:
    int grid[9][9]{};

public:
    explicit Sudoku(int (*grid)[9]) {
        memcpy(this->grid, grid, 9 * 9 * sizeof(int));
    }

    bool operator ==(const int (*otherGrid)[9]) {
        for (int i=0; i<9*9; i++) {
            if (grid[i%9][i/9] != otherGrid[i%9][i/9]) {
                return false;
            }
        }
        return true;
    }

    bool operator ==(const Sudoku & other) {
        for (int i=0; i<9*9; i++) {
#ifdef PRINT
            printf("comparing grid(%d, %d)\n", i%9, i/9);
#endif
            if (grid[i%9][i/9] != other.grid[i%9][i/9]) {
                return false;
            }
        }
        return true;
    }

    int get(int i, int j) {
        if (i >= 0 && i < 9 && j >= 0 && j < 9) {
            return grid[i][j];
        }

        return -1;
    }

    int set(int i, int j, int val) {
        if (i >= 0 && i < 9 && j >= 0 && j < 9) {
            return grid[i][j] = val;
        }
        return -1;
    }

    void print() {
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                printf(" [%d] ", get(i, j));
                if (j == 8) {
                    printf("\n");
                }
            }
        }
    }

    bool solve() {
        return backtrackSolution( grid );
    }
//if grid is full
    bool isUnsolved(int grid[9][9], int &row, int &col) {
        for (row = 0; row < 9; row++)
            for (col = 0; col < 9; col++)
                if (grid[row][col] == 0) return true;
        return false;
    }
//checks row, col and 3x3 box for duplicate number
    bool isSafe(int grid[9][9], int row, int col, int num) {
        return !checkRow(grid, row, num) &&
               !checkCol(grid, col, num) &&
               !checkBox(grid, row - row % 3 ,
                          col - col % 3, num) &&
               grid[row][col] == 0;
    }
//number/location current being worked on
    bool backtrackSolution(int grid[9][9]) {
        int row, col;
        if (!isUnsolved(grid, row, col)) return true;
        for (int num = 1; num <= 9; num++) {
            if (isSafe(grid, row, col, num)) {
                grid[row][col] = num;
                if (backtrackSolution(grid))
                    return true;
                grid[row][col] = 0;
            }
        }
        return false;
    }
//checks row for duplicates
    bool checkRow(int grid[9][9], int row, int num) {
        for (int col = 0; col < 9; col++)
            if (grid[row][col] == num) return true;
        return false;
    }
//checks column for duplicates
    bool checkCol(int grid[9][9], int col, int num) {
        for (int row = 0; row < 9; row++)
            if (grid[row][col] == num) return true;
        return false;
    }
//checks 3x3 for duplicates
    bool checkBox(int grid[9][9], int boxStartRow, int boxStartCol, int num) {
        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
                if (grid[row + boxStartRow] [col + boxStartCol] == num) return true;
        return false;
    }
};
