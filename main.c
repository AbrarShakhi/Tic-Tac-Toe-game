#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
// #include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
// #include <windows.h>
// #include <math.h>

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

void _printBoard(char player)
{
    printf("++|++===========================++|++\n");
    printf("  |        |---|---|---|          |\n");
    printf("  |        | %c | %c | %c |          |\n", board[0][0], board[0][1], board[0][2]);
    printf("  |        |---|---|---|          |\n");
    printf("  |        | %c | %c | %c |          |\n", board[1][0], board[1][1], board[1][2]);
    printf("  |        |---|---|---|          |\n");
    printf("  |        | %c | %c | %c |          |\n", board[2][0], board[2][1], board[2][2]);
    printf("  |        |---|---|---|          |\n");
    printf("++|++===========================++|++\n");
    printf("        '%c' enter your turn: ", player);
}

int _exitTheGame()
{
    printf("++|++===========================++|++\n");
    printf("  |        1) play again          |\n");
    printf("  |        0) exit the game       |\n");
    printf("++|++===========================++|++\n");
    printf("           Enter your choice: ");
    short YorN;
    fflush(stdin);
    scanf("%d", &YorN);
    return YorN;
}

void _welcomeScreen()
{
    printf("++|++===========================++|++\n");
    printf("  |                               |\n");
    printf("  |          TIC TAC TOE          |\n");
    printf("  |                               |\n");
    printf("++|++===========================++|++\n");
    printf("        Prees any key to start");
    fflush(stdin);
    getch();
}

char _randomXO()
{
    srand(time(0));
    if (rand() % 2 == 1)
        return 'X';
    else
        return 'O';
}

void _getTurn(char *move)
{
    fflush(stdin);
    scanf("%c", move);
}

bool _checkAndSetTurn(char player, char move)
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
            if (board[i][j] == move)
            {
                board[i][j] = player;
                return true;
            }
    }
    return false;
}

void _drawMsg()
{
    printf("++|++===========================++|++\n");
    printf("  |                               |\n");
    printf("  |           GAME DRAW           |\n");
    printf("  |                               |\n");
    printf("++|++===========================++|++\n");
}

void _winningMsg(char player)
{
    printf("++|++===========================++|++\n");
    printf("  |                               |\n");
    printf("  |      '%c' WON THE GAME         |\n", player);
    printf("  |                               |\n");
    printf("++|++===========================++|++\n");
}

short _drawOrNot()
{
    short x = 0;
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            if (board[i][j] == 'X' || board[i][j] == 'O') x++;
    return x;
}

bool _processGame(char player, char move)
{
    if (_drawOrNot() == 9)
    {
        _drawMsg();
        return false;
    }

    bool c1, c2, c3, r1, r2, r3, x1, x2, d;

    x1 = (player == board[0][0]) && (player == board[1][1]) && (player == board[2][2]);
    x2 = (player == board[2][0]) && (player == board[1][1]) && (player == board[0][2]);
    r1 = (player == board[0][0]) && (player == board[0][1]) && (player == board[0][2]);
    r2 = (player == board[1][0]) && (player == board[1][1]) && (player == board[1][2]);
    r3 = (player == board[2][0]) && (player == board[2][1]) && (player == board[2][2]);
    c1 = (player == board[0][0]) && (player == board[1][0]) && (player == board[2][0]);
    c2 = (player == board[0][1]) && (player == board[1][1]) && (player == board[2][1]);
    c3 = (player == board[0][2]) && (player == board[1][2]) && (player == board[2][2]);

    if (x1 || x2 || c1 || c2 || c3 || r1 || r2 || r3)
    {
        _winningMsg(player);
        return false;
    }
    return true;
}

void _wrongInputMsg()
{
    printf("\n");
    printf("++|++===========================++|++\n");
    printf("  |          WRONG INPUT          |\n");
}

void _nextPlayer(char *player)
{
    *player = (*player == 'X') ? 'O' : 'X';
}

void _loading(char roll, char move)
{
    system("cls");
    printf("++|++===========================++|++\n");
    printf("  |                               |\n");
    printf("  |              '%c'              |\n", roll);
    printf("  |                               |\n");
    printf("++|++===========================++|++\n");
    printf("              loading..\n");
    sleep(1);
}

void _innitBoardAgain()
{
    char *ptr;
    ptr = &board[0][0];
    char k = '1';
    for (size_t i = 0; i < 9; i++)
        *ptr++ = k++;
}

void _innitBoardToEmpty()
{
    char *ptr;
    ptr = &board[0][0];
    char k = ' ';
    for (size_t i = 0; i < 9; i++)
        *ptr++ = k;
}

int main()
{
    bool isContinue = true;
    char player, move;
    _welcomeScreen();
    do
    {
        system("cls");
        player = _randomXO();
        do
        {
            _printBoard(player);
            _getTurn(&move);

            if (_checkAndSetTurn(player, move))
            {
                _loading(player, move);
                system("cls");
                isContinue = _processGame(player, move);
                if (isContinue == true)
                    _nextPlayer(&player);
            }
            else
                _wrongInputMsg();
        } while (isContinue);
        _innitBoardAgain();

    } while (_exitTheGame() == 1);

    return 0;
}
