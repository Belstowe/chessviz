#include "board.h"

short side_of_piece(char c)
{
    if ((c >= 'A') && (c <= 'Z')) //Capital letter = white.
        return 1;
    
    if ((c >= 'a') && (c <= 'z')) //Lowercase letter = black.
        return -1;

    return 0; //Some other character - that's an error!
}

char cell_column(int cell[2])
{
    return cell[0] + 'a';
}

char cell_row(int cell[2]) {
    return cell[1] + '1';
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