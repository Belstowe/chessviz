#include "board_read.h"
#include "board.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int move_num;
extern char board[8][8];

/* read_string
 * Returns:
 *     -1: Input reaches its limit;
 *     0: User pressed Enter, continuing input;
 *     1: User pressed Ctrl+D, thus ending input;
 */
int read_string(char str_in[], unsigned limit)
{
    for (int i = 0; i < limit - 1; i++) {
        str_in[i] = getchar();

        if (str_in[i] == '\n') {
            str_in[i] = '\0';
            return 0;
        }

        if (str_in[i] == EOF) {
            str_in[i] = '\0';
            return 1;
        }
    }

    printf("/* MOVE %d:\n"
           " * Reading string: WARNING.\n"
           " * Input string has reached its limits.\n"
           " * Some part has been thrown away.\n\n",
           move_num);
    str_in[limit - 1] = '\0';
    return -1;
}

int move_string_split(char* num[], char* move_white[], char* move_black[])
{
    unsigned i = 0, substrs = 0;
    char* str = (*num);

    while (str[i] == ' ')
        i++;
    if (str[i] == '\0')
        return substrs;
    (*num) = &(str[i]);
    substrs++;

    while (str[i] != ' ') {
        if (str[i] == '\0')
            return substrs;
        i++;
    }
    str[i] = '\0';
    i++;

    while (str[i] == ' ')
        i++;
    if (str[i] == '\0')
        return substrs;
    (*move_white) = &(str[i]);
    substrs++;

    while (str[i] != ' ') {
        if (str[i] == '\0')
            return substrs;
        i++;
    }
    str[i] = '\0';
    i++;

    while (str[i] == ' ')
        i++;
    if (str[i] == '\0')
        return substrs;
    (*move_black) = &(str[i]);
    substrs++;

    while (str[i] != ' ') {
        if (str[i] == '\0')
            return substrs;
        i++;
    }
    str[i] = '\0';

    return substrs;
}

char check_piece(char move[])
{
    if ((move[0] == 'K') || (move[0] == 'Q') || (move[0] == 'R')
        || (move[0] == 'B') || (move[0] == 'N'))
        return move[0];
    else
        return 'P';
}

unsigned check_move_col(char move[], int cell[2])
{
    unsigned i = 0;
    while (((move[i] < 'a') || (move[i] > 'h')) && (move[i] != '\0'))
        i++;

    if (move[i] != '\0')
        cell[0] = move[i] - 'a';
    else
        cell[0] = -1;

    return i;
}

unsigned check_move_row(char move[], int cell[2])
{
    unsigned i = 0;
    while (((move[i] < '1') || (move[i] > '8')) && (move[i] != '\0'))
        i++;

    if (move[i] != '\0')
        cell[1] = move[i] - '1';
    else
        cell[1] = -1;

    return i;
}

char check_move_type(char* move[])
{
    char* pointer = *move;
    unsigned i = 0;
    while ((pointer[i] != '-') && (pointer[i] != 'x') && (pointer[i] != '\0'))
        i++;

    *move = &(pointer[i + 1]);
    return pointer[i];
}

char check_move_situation(char move[])
{
    unsigned i = 0;
    while ((move[i] != '#') && (move[i] != '+') && (move[i] != '\0'))
        i++;

    return move[i];
}

int check_white_move(char move[])
{
    char piece = check_piece(move);
    if (piece != 'P')
        move = &(move[1]);

    int orig_cell[2];
    int pos;
    pos = check_move_col(move, orig_cell);
    pos -= check_move_row(move, orig_cell);
    if (orig_cell[0] == -1 || orig_cell[1] == -1) {
        printf("/* MOVE %d:\n"
               " * Checking move of white: ERROR.\n"
               " * Couldn't find original move specification.\n\n",
               move_num);
        return -1;
    }

    if (pos > 0)
        printf("/* MOVE %d:\n"
               " * Checking move of white: WARNING.\n"
               " * Found out that original move literal is located after move "
               "number.\n"
               " * Might be the consequence of a corruption.\n\n",
               move_num);

    if (board[orig_cell[1]][orig_cell[0]] != piece)
        printf("/* MOVE %d:\n"
               " * Checking move of white: WARNING.\n"
               " * No %s on original cell: %c%c.\n"
               " * This for sure will lead to chessboard curiosities!\n\n",
               move_num,
               piece_name_print(piece),
               cell_column(orig_cell),
               cell_row(orig_cell));

    int type = check_move_type(&move);
    if (type == '\0') {
        printf("/* MOVE %d:\n"
               " * Checking move of white: ERROR.\n"
               " * Couldn't find move type.\n\n",
               move_num);
        return -1;
    }

    int goto_cell[2];
    pos = check_move_col(move, goto_cell);
    pos -= check_move_row(move, goto_cell);

    if (goto_cell[0] == -1 || goto_cell[1] == -1) {
        printf("/* MOVE %d:\n"
               " * Checking move of white: ERROR.\n"
               " * Couldn't find go-to move specification.\n\n",
               move_num);
        return -1;
    }

    if (pos > 0)
        printf("/* MOVE %d:\n"
               " * Checking move of white: WARNING.\n"
               " * Found out that go-to move literal is located after move "
               "number.\n"
               " * Might be the consequence of a corruption.\n\n",
               move_num);

    board[orig_cell[1]][orig_cell[0]] = ' ';
    board[goto_cell[1]][goto_cell[0]] = piece;

    if (check_move_situation(move) == '#')
        return 1;

    return 0;
}

int check_black_move(char move[])
{
    char piece = check_piece(move) - 'A' + 'a';
    if (piece != 'p')
        move = &(move[1]);

    int orig_cell[2];
    int pos;
    pos = check_move_col(move, orig_cell);
    pos -= check_move_row(move, orig_cell);
    if (orig_cell[0] == -1 || orig_cell[1] == -1) {
        printf("/* MOVE %d:\n"
               " * Checking move of black: ERROR.\n"
               " * Couldn't find original move specification.\n\n",
               move_num);
        return -1;
    }

    if (pos > 0)
        printf("/* MOVE %d:\n"
               " * Checking move of black: WARNING.\n"
               " * Found out that original move literal is located after move "
               "number.\n"
               " * Might be the consequence of a corruption.\n\n",
               move_num);

    if (board[orig_cell[1]][orig_cell[0]] != piece)
        printf("/* MOVE %d:\n"
               " * Checking move of black: WARNING.\n"
               " * No %s on original cell: %c%c.\n"
               " * This for sure will lead to chessboard curiosities!\n\n",
               move_num,
               piece_name_print(piece),
               cell_column(orig_cell),
               cell_row(orig_cell));

    int type = check_move_type(&move);
    if (type == '\0') {
        printf("/* MOVE %d:\n"
               " * Checking move of black: ERROR.\n"
               " * Couldn't find move type.\n\n",
               move_num);
        return -1;
    }

    int goto_cell[2];
    pos = check_move_col(move, goto_cell);
    pos -= check_move_row(move, goto_cell);

    if (goto_cell[0] == -1 || goto_cell[1] == -1) {
        printf("/* MOVE %d:\n"
               " * Checking move of black: ERROR.\n"
               " * Couldn't find go-to move specification.\n\n",
               move_num);
        return -1;
    }

    if (pos > 0)
        printf("/* MOVE %d:\n"
               " * Checking move of black: WARNING.\n"
               " * Found out that go-to move literal is located after move "
               "number.\n"
               " * Might be the consequence of a corruption.\n\n",
               move_num);

    board[orig_cell[1]][orig_cell[0]] = ' ';
    board[goto_cell[1]][goto_cell[0]] = piece;

    if (check_move_situation(move) == '#')
        return 1;

    return 0;
}

int check_num(char num[])
{
    unsigned i = 0;
    for (; (num[i] != '\0') && (num[i] != '.'); i++)
        if ((num[i] < '0') || (num[i] > '9')) {
            printf("/* MOVE %d:\n"
                   " * Checking number: WARNING.\n"
                   " * Either what we are checking is NOT a number or it has "
                   "alien characters.\n"
                   " * Might be the reason to further problems.\n\n",
                   move_num);
            return -1;
        }

    if (num[i] != '.')
        printf("/* MOVE %d:\n"
               " * Checking number: WARNING.\n"
               " * No dot in the end of move's num.\n"
               " * Might be the reason to further problems.\n\n",
               move_num);
    else
        num[i] = '\0';

    if (move_num != atoi(num))
        printf("/* MOVE %d:\n"
               " * Checking number: WARNING.\n"
               " * The move specified (%s) is not equal to current move.\n"
               " * Might be the reason to further problems.\n\n",
               move_num,
               num);

    return 0;
}