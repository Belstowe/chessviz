#include "board_print_plain.h"
#include <stdio.h>

void board_print_plain(char board[8][8]) {
    for (int i = 8; i > 0; i--) {
        printf("%d ", i);
        for (int j = 0; j < 8; j++) {
            printf("%c ", board[i - 1][j]);
        }
        printf("\n");
    }
    printf("  ");
    for (int i = 0; i < 8; i++)
        printf("%c ", i + 'a');
    printf("\n");
}