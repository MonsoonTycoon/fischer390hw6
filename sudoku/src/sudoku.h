#include <iostream>
#include <cstring>

class Sudoku {
private:
    int grid[9][9]{};

public:
    explicit Sudoku(int (*grid)[9]) {
        memcpy(this->grid, grid, 9 * 9 * sizeof(int));
    }

    bool operator ==(const int (*otherGrid)[9]) {
        for (int i=0; i<9*9; i++) {
            if (grid[i%3][i/3] != otherGrid[i%3][i/3]) {
                return false;
            }
        }
        return true;
    }

    bool operator ==(const Sudoku & other) {
        for (int i=0; i<9*9; i++) {
            if (grid[i%3][i/3] != other.grid[i%3][i/3]) {
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
        return SolveSudoku( grid );
    }

    bool unsolved(int grid[9][9],
                                int &row, int &col) {
        for (row = 0; row < 9; row++)
            for (col = 0; col < 9; col++)
                if (grid[row][col] == 0)
                    return true;
        return false;
    }

    bool isSafe(int grid[9][9], int row,
                int col, int num) {
        return !UsedInRow(grid, row, num) &&
               !UsedInCol(grid, col, num) &&
               !UsedInBox(grid, row - row % 3 ,
                          col - col % 3, num) &&
               grid[row][col] == 0;
    }
    
    bool SolveSudoku(int grid[9][9]) {
        int row, col;
        // If there is no unassigned location,
        // we are done
        if (!unsolved(grid, row, col))
            return true; // success!
        // consider digits 1 to 9
        for (int num = 1; num <= 9; num++)
        {
            // if looks promising
            if (isSafe(grid, row, col, num))
            {
                // make tentative assignment
                grid[row][col] = num;
                // return, if success, yay!
                if (SolveSudoku(grid))
                    return true;
                // failure, unmake & try again
                grid[row][col] = 0;
            }
        }
        return false; // this triggers backtracking
    }

/* Returns a boolean which indicates whether
an assigned entry in the specified row matches
the given number. */
    bool UsedInRow(int grid[9][9], int row, int num) {
        for (int col = 0; col < 9; col++)
            if (grid[row][col] == num)
                return true;
        return false;
    }

/* Returns a boolean which indicates whether
an assigned entry in the specified column
matches the given number. */
    bool UsedInCol(int grid[9][9], int col, int num) {
        for (int row = 0; row < 9; row++)
            if (grid[row][col] == num)
                return true;
        return false;
    }

/* Returns a boolean which indicates whether
an assigned entry within the specified 3x3 box
matches the given number. */
    bool UsedInBox(int grid[9][9], int boxStartRow,
                   int boxStartCol, int num) {
        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
                if (grid[row + boxStartRow]
                    [col + boxStartCol] == num)
                    return true;
        return false;
    }

};
