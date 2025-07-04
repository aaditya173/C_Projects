#include <stdio.h>
#include <stdbool.h>

#define N 9

int conut = 0;

void printSudoku(int sudoku[N][N]);
// bool isValid(int sudoku[N][N]);
bool isValidMove(int sudoku[N][N], int row, int col, int value);
bool sudokuSolver(int sudoku[N][N], int row, int col);

int main()
{
    // int sudoku[N][N] = {
    //     {3, 0, 0, 0, 2, 0, 0, 7, 0},
    //     {9, 0, 0, 5, 0, 0, 0, 1, 4},
    //     {0, 1, 6, 3, 7, 0, 0, 0, 8},
    //     {2, 0, 0, 8, 0, 0, 0, 0, 1},
    //     {5, 0, 0, 0, 4, 1, 8, 0, 0},
    //     {0, 8, 9, 0, 0, 0, 0, 5, 0},
    //     {0, 0, 5, 0, 1, 0, 2, 8, 0},
    //     {0, 4, 0, 0, 0, 6, 0, 9, 3},
    //     {7, 3, 1, 0, 8, 2, 0, 0, 0}};

    int sudoku[N][N] = {
        {5, 3, 0, 0, 0, 0, 0, 0, 0},
        {6, 2, 0, 3, 0, 0, 0, 0, 0},
        {0, 9, 0, 0, 4, 0, 1, 0, 0},
        {0, 5, 0, 4, 8, 0, 2, 9, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 4, 3, 0, 1, 2, 0, 5, 0},
        {0, 0, 8, 0, 5, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 6, 0, 3, 9},
        {0, 0, 0, 0, 0, 0, 0, 6, 2}
    };

    printSudoku(sudoku);

    sudokuSolver(sudoku, 0, 0);

    printSudoku(sudoku);

    return 0;
}

void printSudoku(int sudoku[N][N])
{
    printf("+-------+-------+-------+\n");
    for (int row = 0; row < 9; row++)
    {
        printf("| ");
        for (int col = 0; col < 9; col++)
        {
            if (sudoku[row][col] != 0)
                printf("%d ", sudoku[row][col]);
            else
                printf("  ");
            if (col % 3 == 2)
                printf("| ");
        }
        printf("\n");
        if (row % 3 == 2 && row != 8)
        {
            printf("|-------+-------+-------|\n");
        }
    }
    printf("+-------+-------+-------+\n");
}
// bool isValid(int sudoku[N][N])
// {
//
// }
bool isValidMove(int sudoku[N][N], int row, int col, int value)
{
    // check for the row
    for (int i = 0; i < N; i++)
    {
        if (sudoku[row][i] == value)
            return false;
    }
    // check for the cloumn
    for (int i = 0; i < N; i++)
    {
        if (sudoku[i][col] == value)
            return false;
    }
    // check for the square
    int r, c;
    r = row - (row % 3);
    c = col - (col % 3);
    for (int i = r; i < r + 3; i++)
    {
        for (int j = c; j < c + 3; j++)
        {
            if (sudoku[i][j] == value)
                return false;
        }
    }
    return true;
}
bool sudokuSolver(int sudoku[N][N], int row, int col)
{
    if (9 == col)
    {
        row++;
        col = 0;
        if (9 == row)
            return true;
    }

    if (sudoku[row][col] != 0)
    {
        return sudokuSolver(sudoku, row, col + 1);
    }

    for (int k = 1; k <= 9; k++)
    {
        if (isValidMove(sudoku, row, col, k))
        {
            sudoku[row][col] = k;
            if (sudokuSolver(sudoku, row, col + 1))
            {
                return true;
            }
            sudoku[row][col] = 0;
        }
    }
    return false;
}