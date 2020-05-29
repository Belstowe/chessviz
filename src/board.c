#include "board.h"

#include <stdlib.h>

#define MAX_STRING_LENGTH 256

short side_of_piece(char c)
{
    if ((c >= 'A') && (c <= 'Z')) // Capital letter = white.
        return 1;

    if ((c >= 'a') && (c <= 'z')) // Lowercase letter = black.
        return -1;

    return 0; // Some other character - that's an error!
}

char cell_column(Cell* cell)
{
    return cell->column + 'a';
}

char cell_row(Cell* cell)
{
    return cell->row + '1';
}

unsigned check_move_col(const char move[], Cell* cell)
{
    unsigned i = 0;
    while (((move[i] < 'a') || (move[i] > 'h')) && (move[i] != '\0'))
        i++;

    if (move[i] != '\0')
        cell->column = move[i] - 'a';
    else
        cell->column = -1;

    return i;
}

unsigned check_move_row(const char move[], Cell* cell)
{
    unsigned i = 0;
    while (((move[i] < '1') || (move[i] > '8')) && (move[i] != '\0'))
        i++;

    if (move[i] != '\0')
        cell->row = move[i] - '1';
    else
        cell->row = -1;

    return i;
}

Cell* cell_compose(const char cell_str[])
{
    Cell* result_cell = malloc(sizeof(Cell));

    check_move_row(cell_str, result_cell);
    check_move_col(cell_str, result_cell);

    return result_cell;
}

char* piece_name_print(char c)
{
    switch (c) {
    case 'r':
        return "Black Rook";
    case 'n':
        return "Black Knight";
    case 'b':
        return "Black Bishop";
    case 'q':
        return "Black Queen";
    case 'k':
        return "Black King";
    case 'p':
        return "Black Pawn";
    case 'R':
        return "White Rook";
    case 'N':
        return "White Knight";
    case 'B':
        return "White Bishop";
    case 'Q':
        return "White Queen";
    case 'K':
        return "White King";
    case 'P':
        return "White Pawn";
    case ' ':
        return "None";
    default:
        return "Unknown";
    }
}

char* to_lower_case(char str[])
{
    char* new_str = malloc(MAX_STRING_LENGTH * sizeof(char));

    unsigned i = 0;
    for (; str[i] != '\0'; i++)
        if ((str[i] >= 'A') && (str[i] <= 'Z'))
            new_str[i] = str[i] - 'A' + 'a';
        else
            new_str[i] = str[i];

    new_str[i] = '\0';
    return new_str;
}