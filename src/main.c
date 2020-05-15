#define MAX_STRING_SIZE 256
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "board_print_html.h"
#include "board_print_plain.h"
#include "board_read.h"

int move_num = 1;
char board[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};

int main()
{
    char* input_string = malloc(MAX_STRING_SIZE * sizeof(char));
    char* white_move_pointer;
    char* black_move_pointer;
    int status = 0;
    unsigned substrs;

    printf("Welcome to Chessviz!\nThis program is used to interprete moves on "
           "chessboard.\n\nExample:\n1. e2-e4 e7-e5\n2. Bf1-c4 Nb8-c6\n3. "
           "Qd1-h5 Ng8-f6\n4. Qh5xf7#\n\nPress Ctrl+D to stop input and view "
           "chessboard.\n");

    while (status != 1) {
        status = read_string(input_string, MAX_STRING_SIZE);
        substrs = move_string_split(
                &input_string, &white_move_pointer, &black_move_pointer);
        if (substrs < 2)
            break;
        else if (substrs == 2) {
            if (check_white_move(input_string))
                break;

            board_print_plain(board);

            if (check_black_move(white_move_pointer))
                break;

            board_print_plain(board);
        } else if (substrs == 3) {
            if (check_num(input_string))
                break;

            if (check_white_move(white_move_pointer))
                break;

            board_print_plain(board);

            if (check_black_move(black_move_pointer))
                break;

            board_print_plain(board);
        }

        move_num++;
    }

    board_print_plain(board);
}
