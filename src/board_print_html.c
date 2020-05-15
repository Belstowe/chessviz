#include "board_print_html.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 256

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

int board_print_html(char board[8][8], const char* file_name)
{
    // Making write access to file
    FILE* html = fopen(file_name, "w");
    if (html == NULL) {
        printf("ERROR. Can't access %s.\n", file_name);
        return -1;
    }

    fprintf(html,
            R"(
            <!DOCTYPE html>
			<html>
			<head>
				<meta charset="utf-8"
				<title>chessviz</title>
				<style type="text/css">
					table.chessboard {
						border: 5px solid #333;
    					border-collapse: collapse;
    					height: 320px;
    					margin: 20px;
     					width: 320px;
					}
					table.chessboard caption {
						text-align: left;
					}
					table.chessboard td {
						background-color: #fff;
    					font-size: 25px;
    					height: 40px;
    					text-align: center;
    					vertical-align: middle;
    					width: 40px;
					}
					table.chessboard tr:nth-child(odd) td:nth-child(even),
					table.chessboard tr:nth-child(even) td:nth-child(odd) {
						background-color: #999;
					}

					table.chessboard .white.king:before   { content: "\2654"; }
    				table.chessboard .white.queen:before  { content: "\2655"; }
    				table.chessboard .white.rook:before   { content: "\2656"; }
   					table.chessboard .white.bishop:before { content: "\2657"; }
    				table.chessboard .white.knight:before { content: "\2658"; }
    				table.chessboard .white.pawn:before   { content: "\2659"; }

    				table.chessboard .black.king:before   { content: "\265A"; }
    				table.chessboard .black.queen:before  { content: "\265B"; }
    				table.chessboard .black.rook:before   { content: "\265C"; }
    				table.chessboard .black.bishop:before { content: "\265D"; }
    				table.chessboard .black.knight:before { content: "\265E"; }
    				table.chessboard .black.pawn:before   { content: "\265F"; }
    			</style>
    		</head>

    		<body>
    			<table class="chessboard">)");

    for (int i = 7; i >= 0; i--) {
        fprintf(html,
                R"(
                    <tr>)");
        for (int j = 0; j < 8; j++) {
            fprintf(html,
                    R"(
                        <td>)");

            if (board[i][j] != ' ')
                fprintf(html,
                        "<span class=\"%s\"></span>",
                        to_lower_case(piece_name_print(board[i][j])));

            fprintf(html, R"(</td>)");
        }
        fprintf(html,
                R"(
                    </tr>)");
    }

    fprintf(html,
            R"(
    			</table>
    		</body>
    		</html>)");

    return 0;
}