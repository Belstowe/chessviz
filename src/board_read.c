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

/* check_move_validity
 * Returns:
 *     0 - success;
 *     1 - A Pawn can't move further than 1 cell forward (or 2 cells in case of
 * starting position)! 2 - A Pawn can't go to other column unless by chopping an
 * enemy piece! 3 - A Pawn always chops in diagonal, forward by a cell and side
 * by a cell!
 */
int check_move_validity(
        char piece, int type, int orig_cell[2], int goto_cell[2])
{
    switch (piece) {
    case 'P':
        if (type == '-') {
            if (cell_row(orig_cell) == '2') {
                if ((cell_row(goto_cell) != '3')
                    && (cell_row(goto_cell) != '4'))
                    return 1;
            } else {
                if (cell_row(goto_cell) - cell_row(orig_cell) != 1)
                    return 1;
            }

            if (cell_column(goto_cell) != cell_column(orig_cell))
                return 2;
        } else if (type == 'x') {
            if ((cell_column(orig_cell) - cell_column(goto_cell) != 1)
                && (cell_column(goto_cell) - cell_column(orig_cell) != 1))
                return 3;

            if (cell_row(goto_cell) - cell_row(orig_cell) != 1)
                return 3;
        }
        break;

    case 'p':
        if (type == '-') {
            if (cell_row(orig_cell) == '7') {
                if ((cell_row(goto_cell) != '6')
                    && (cell_row(goto_cell) != '5'))
                    return 1;
            } else {
                if (cell_row(orig_cell) - cell_row(goto_cell) != 1)
                    return 1;
            }

            if (cell_column(goto_cell) != cell_column(orig_cell))
                return 2;
        } else if (type == 'x') {
            if ((cell_column(orig_cell) - cell_column(goto_cell) != 1)
                && (cell_column(goto_cell) - cell_column(orig_cell) != 1))
                return 3;

            if (cell_row(orig_cell) - cell_row(goto_cell) != 1)
                return 3;
        }
        break;
    }

    return 0;
}

void interprete_validity(int code)
{
    if (code == 0)
        return;

    switch (code) {
    case 1:
        printf(" * A Pawn can't move further than 1 cell forward (or 2 cells "
               "in case of starting position)!\n\n");
        break;

    case 2:
        printf(" * A Pawn can't go to other column unless by chopping an enemy "
               "piece!\n\n");
        break;

    case 3:
        printf(" * A Pawn always chops in diagonal, forward by a cell and side "
               "by a cell!\n\n");
        break;
    }
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

    interprete_validity(check_move_validity(piece, type, orig_cell, goto_cell));
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

    interprete_validity(check_move_validity(piece, type, orig_cell, goto_cell));
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