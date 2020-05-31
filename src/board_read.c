#include "board_read.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int move_num;

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

/* move_string_split
 * Splits string to three specific substrings: number of move, move of white and
 * move of black. Returns: 1?? - got num; ?1? - got move_white;
 * ??1 - got move_black;
 * 0 - got nothing.
 */
int move_string_split(char* num[], char* move_white[], char* move_black[])
{
    unsigned i = 0;
    unsigned short num_checked = 0, move_white_checked = 0,
                   move_black_checked = 0;
    char* str = (*num);

    for (; str[i] != '\0'; i++) {
        if (str[i] == ' ')
            continue;

        if ((str[i] >= '1') && (str[i] <= '9') && (!num_checked)) {
            (*num) = &(str[i]);
            num_checked = 1;
        } else {
            if (!move_white_checked) {
                (*move_white) = &(str[i]);
                move_white_checked = 1;
            } else if (!move_black_checked) {
                (*move_black) = &(str[i]);
                move_black_checked = 1;
            }
        }

        while ((str[i] != ' ') && (str[i] != '\0'))
            i++;

        if (str[i] == '\0')
            break;
        else
            str[i] = '\0';
    }

    return (100 * num_checked + 10 * move_white_checked + move_black_checked);
}

char check_piece(char move[])
{
    if ((move[0] == 'K') || (move[0] == 'Q') || (move[0] == 'R')
        || (move[0] == 'B') || (move[0] == 'N'))
        return move[0];
    else
        return 'P';
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

enum ValidateCode
check_move_validity(char piece, int type, Cell* orig_cell, Cell* goto_cell)
{
    int row_moved = row_shift(orig_cell, goto_cell);
    int col_moved = column_shift(orig_cell, goto_cell);

    if ((row_moved == 0) && (col_moved == 0))
        return NoMove;

    switch (piece) {
    case 'P':
        if (type == '-') {
            if (cell_row(orig_cell) == '2') {
                if ((row_moved < 0) || (row_moved > 2))
                    return PawnRowSwitchError;
            } else {
                if (row_moved != 1)
                    return PawnRowSwitchError;
            }

            if (cell_column(goto_cell) != cell_column(orig_cell))
                return PawnColumnSwitchNoChop;
        } else if (type == 'x') {
            if (absolute(col_moved) != 1)
                return PawnChopWrong;

            if (row_moved != 1)
                return PawnChopWrong;
        }
        break;

    case 'p':
        if (type == '-') {
            if (cell_row(orig_cell) == '7') {
                if ((row_moved > 0) || (row_moved < -2))
                    return PawnRowSwitchError;
            } else {
                if (row_moved != -1)
                    return PawnRowSwitchError;
            }

            if (cell_column(goto_cell) != cell_column(orig_cell))
                return PawnColumnSwitchNoChop;
        } else if (type == 'x') {
            if (absolute(col_moved) != 1)
                return PawnChopWrong;

            if (row_moved != -1)
                return PawnChopWrong;
        }
        break;

    case 'N':
    case 'n':
        if (!((absolute(row_moved) == 2)
              && (absolute(col_moved)
                  == 1))) // Knight move is supposed to be shift by 2 cells one
                          // side and 1 cell the other side
            if (!((absolute(row_moved) == 1) && (absolute(col_moved) == 2)))
                return KnightMoveWrong;
        break;

    case 'B':
    case 'b':
        if (!(absolute(row_moved)
              == absolute(col_moved))) // If did not move by diagonal...
            return BishopMoveWrong;
        break;

    case 'R':
    case 'r':
        if (!(absolute(row_moved) > 0
              && !col_moved)) // If did not move by vertical...
            if (!(absolute(col_moved) > 0
                  && !row_moved)) // And did not move by horizontal...
                return RookMoveWrong;
        break;

    case 'Q':
    case 'q':
        if (!(absolute(row_moved) > 0
              && !col_moved)) // If did not move by vertical...
            if (!(absolute(col_moved) > 0
                  && !row_moved)) // And did not move by horizontal...
                if (!(absolute(row_moved)
                      == absolute(
                              col_moved))) // And did not move by diagonal...
                    return QueenMoveWrong;
        break;

    case 'K':
    case 'k':
        if ((absolute(row_moved) > 1)
            || (absolute(col_moved)
                > 1)) // If a move goes beyond a 1-cell square around king...
            return KingMoveWrong;
        break;
    }

    return Valid;
}

void interprete_validity(enum ValidateCode code)
{
    switch (code) {
    case NoMove:
        printf(" * No move shift detected at all!\n\n");
        break;

    case PawnRowSwitchError:
        printf(" * A Pawn can't move further than 1 cell forward (or 2 cells "
               "in case of starting position)!\n\n");
        break;

    case PawnColumnSwitchNoChop:
        printf(" * A Pawn can't go to other column unless by chopping an enemy "
               "piece!\n\n");
        break;

    case PawnChopWrong:
        printf(" * A Pawn always chops in diagonal, forward by a cell and side "
               "by a cell!\n\n");
        break;

    case KnightMoveWrong:
        printf(" * Knight's move is supposed to be shift by 2 cells one side "
               "and 1 cell the other side!\n\n");
        break;

    case BishopMoveWrong:
        printf(" * Bishops always move by diagonal!\n\n");
        break;

    case RookMoveWrong:
        printf(" * Rooks always move either by horizontal OR by vertical!\n\n");
        break;

    case QueenMoveWrong:
        printf(" * Queens always move either by horizontal, by vertical OR by "
               "diagonal!\n\n");
        break;

    case KingMoveWrong:
        printf(" * Kings always move in borders of 1 cell square around them!");
        break;

    default:
        break;
    }
}

int check_white_move(char board[8][8], char move[])
{
    char piece = check_piece(move);
    if (piece != 'P')
        move = &(move[1]);

    Cell* orig_cell = malloc(sizeof(Cell));
    int pos;
    pos = check_move_col(move, orig_cell);
    pos -= check_move_row(move, orig_cell);
    if (orig_cell->column == -1 || orig_cell->row == -1) {
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

    if (board[orig_cell->row][orig_cell->column] != piece)
        printf("/* MOVE %d:\n"
               " * Checking move of white: WARNING.\n"
               " * No %s on original cell: %s.\n"
               " * This for sure will lead to chessboard curiosities!\n\n",
               move_num,
               piece_name_print(piece),
               cell_decompose(orig_cell));

    int type = check_move_type(&move);
    if (type == '\0') {
        printf("/* MOVE %d:\n"
               " * Checking move of white: ERROR.\n"
               " * Couldn't find move type.\n\n",
               move_num);
        return -1;
    }

    Cell* goto_cell = malloc(sizeof(Cell));
    pos = check_move_col(move, goto_cell);
    pos -= check_move_row(move, goto_cell);

    if (goto_cell->column == -1 || goto_cell->row == -1) {
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
    board[orig_cell->row][orig_cell->column] = ' ';
    board[goto_cell->row][goto_cell->column] = piece;

    if (check_move_situation(move) == '#')
        return 1;

    return 0;
}

int check_black_move(char board[8][8], char move[])
{
    char piece = check_piece(move) - 'A' + 'a';
    if (piece != 'p')
        move = &(move[1]);

    Cell* orig_cell = malloc(sizeof(Cell));
    int pos;
    pos = check_move_col(move, orig_cell);
    pos -= check_move_row(move, orig_cell);
    if (orig_cell->column == -1 || orig_cell->row == -1) {
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

    if (board[orig_cell->row][orig_cell->column] != piece)
        printf("/* MOVE %d:\n"
               " * Checking move of black: WARNING.\n"
               " * No %s on original cell: %s.\n"
               " * This for sure will lead to chessboard curiosities!\n\n",
               move_num,
               piece_name_print(piece),
               cell_decompose(orig_cell));

    int type = check_move_type(&move);
    if (type == '\0') {
        printf("/* MOVE %d:\n"
               " * Checking move of black: ERROR.\n"
               " * Couldn't find move type.\n\n",
               move_num);
        return -1;
    }

    Cell* goto_cell = malloc(sizeof(Cell));
    pos = check_move_col(move, goto_cell);
    pos -= check_move_row(move, goto_cell);

    if (goto_cell->column == -1 || goto_cell->row == -1) {
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
    board[orig_cell->row][orig_cell->column] = ' ';
    board[goto_cell->row][goto_cell->column] = piece;

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