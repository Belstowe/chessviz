#include "board_print_html.h"
#include <stdio.h>

void to_lower_case(char str[])
{
    for (unsigned i = 0; str[i] != '\0'; i++)
        if ((str[i] >= 'A') && (str[i] <= 'Z'))
            str[i] = str[i] - 'A' + 'a';
}

void board_print_html(char board[8][8], const char* file_name)
{
    // Making write access to file
    FILE* html = fopen(file_name, "w");
    if (html == NULL) {
        printf("ERROR. Can't access %s.\n", file_name);
        return;
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

    fprintf(html,
    		R"(
    			</table>
    		</body>
    		</html>)");
}