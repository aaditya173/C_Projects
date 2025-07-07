#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int player;
    int computer;
    int draw;
} Score;

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'
int difficulty;
Score score = {.player = 0, .computer = 0, .draw = 0};

void clearScreen();
void inputDifficulty();
void printBoard(char tttBoard[BOARD_SIZE][BOARD_SIZE]);
int checkWin(char tttBoard[BOARD_SIZE][BOARD_SIZE], char player);
int checkDraw(char tttBoard[BOARD_SIZE][BOARD_SIZE]);
void playGame();
void playerMove(char tttBoard[BOARD_SIZE][BOARD_SIZE]);
void computerMove(char tttBoard[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

int main()
{
    srand(time(NULL));
    int playAgain;
    do
    {
        inputDifficulty();
        playGame();
        printf("Play again ? (1 for yes and 0 for no) : ");
        scanf("%d", &playAgain);
    } while (playAgain != 0);

    return 0;
}

void clearScreen()
{
#if defined(__linux__) || defined(__unix__) || defined(__apple__)
    system("clear");
#elif defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}
void inputDifficulty()
{
    while (1)
    {
        printf("Select Difficulty Level :\n");
        printf("1. Easy Mode\n");
        printf("2. Hard Mode\n");
        printf("Enter you choice : ");
        scanf("%d", &difficulty);
        if (difficulty != 1 && difficulty != 2)
        {
            printf("Incorrect Choice enter(1/2)!!\n");
        }
        else
        {
            break;
        }
    }
}
void printBoard(char tttBoard[BOARD_SIZE][BOARD_SIZE])
{
    clearScreen();
    printf("Score - Player : %d, Computer : %d, Draw : %d\n", score.player, score.computer, score.draw);
    printf("Tic-Tac-Toe\n");

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            printf(" %c ", tttBoard[row][col]);
            if (col != 2)
                printf("|");
        }
        if (row != 2)
            printf("\n---+---+---\n");
    }
}
int checkWin(char tttBoard[BOARD_SIZE][BOARD_SIZE], char player)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (tttBoard[i][0] == player && tttBoard[i][1] == player && tttBoard[i][2] == player)
        {
            return 1;
        }
        if (tttBoard[0][i] == player && tttBoard[1][i] == player && tttBoard[2][i] == player)
        {
            return 1;
        }
    }
    if ((tttBoard[0][0] == player && tttBoard[1][1] == player && tttBoard[2][2] == player) || (tttBoard[0][2] == player && tttBoard[1][1] == player && tttBoard[2][0] == player))
    {
        return 1;
    }
    return 0;
}
int checkDraw(char tttBoard[BOARD_SIZE][BOARD_SIZE])
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (' ' == tttBoard[row][col])
                return 0;
        }
    }
    return 1;
}
void playGame()
{
    char tttBoard[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

    printBoard(tttBoard);

    char currentPlayer = rand() % 2 == 0 ? X : O;

    while (1)
    {
        if (currentPlayer == X)
        {
            playerMove(tttBoard);
            printBoard(tttBoard);
            if (checkWin(tttBoard, X))
            {
                score.player++;
                printBoard(tttBoard);
                printf("\nCongratulations! You have won!!\n");
                return;
            }
            currentPlayer = O;
        }
        else
        {
            computerMove(tttBoard);
            printBoard(tttBoard);
            if (checkWin(tttBoard, O))
            {
                score.computer++;
                printBoard(tttBoard);
                printf("\nComputer Won.!!\n");
                return;
            }
            currentPlayer = X;
        }
        if (checkDraw(tttBoard))
        {
            score.draw++;
            printBoard(tttBoard);
            printf("\nIt is a Draw Match\n");
            return;
        }
    }
}
void playerMove(char tttBoard[BOARD_SIZE][BOARD_SIZE])
{
    int count = 0, x, y;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (tttBoard[i][j] == ' ')
            {
                count++;
                x = i;
                y = j;
            }
        }
    }

    if (count == 1)
    {
        tttBoard[x][y] = X;
        return;
    }

    int row, col;
    do
    {
        printf("\nPlayer X's turn.");
        printf("\nEnter row and column (1-3) for X (e.g., 1 3): ");
        scanf("%d %d", &row, &col);
        row--;
        col--; // converting to zero based
    } while (!is_valid_move(tttBoard, row, col));
    tttBoard[row][col] = X;
}
void computerMove(char tttBoard[BOARD_SIZE][BOARD_SIZE])
{

    // 1. For Immediate Win
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (tttBoard[row][col] == ' ')
            {
                tttBoard[row][col] = O;
                if (checkWin(tttBoard, O))
                {
                    return;
                }
                else
                {
                    tttBoard[row][col] = ' ';
                }
            }
        }
    }

    // 2. Check for Immediate Block
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (tttBoard[row][col] == ' ')
            {
                tttBoard[row][col] = X;
                if (checkWin(tttBoard, X))
                {
                    tttBoard[row][col] = O;
                    return;
                }
                else
                {
                    tttBoard[row][col] = ' ';
                }
            }
        }
    }

    if (difficulty == 2)
    {
        // 3. For Center
        if (tttBoard[1][1] == ' ')
        {
            tttBoard[1][1] = O;
            return;
        }

        // 4. For Cornors
        int corner[4][2] = {
            {0, 0},
            {0, 2},
            {2, 0},
            {2, 2}};
        for (int i = 0; i < 4; i++)
        {
            if (tttBoard[corner[i][0]][corner[i][1]] == ' ')
            {
                tttBoard[corner[i][0]][corner[i][1]] = O;
                return;
            }
        }
    }

    // 5. First Available Place
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (tttBoard[row][col] == ' ')
            {
                tttBoard[row][col] = O;
                return;
            }
        }
    }
}
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
    return !(row < 0 || col < 0 ||
             row > 2 || col > 2 ||
             board[row][col] != ' ');
}
