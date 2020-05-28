#include <board.h>

#include <ctest.h>

CTEST(side_of_piece, piece_side)
{
    const char white_piece = 'K';
    const char black_piece = 'b';
    const char unknown = '?';

    const int white_side_result = side_of_piece(white_piece);
    const int black_side_result = side_of_piece(black_piece);
    const int unknown_result = side_of_piece(unknown);

    ASSERT_EQUAL(white_side_result, 1);
    ASSERT_EQUAL(black_side_result, -1);
    ASSERT_EQUAL(unknown_result, 0);
}

CTEST(correct_cell, cell_correct_name)
{
    // We will take g2 for example
    int cell[2];
    cell[0] = 6; // g
    cell[1] = 1; // 2

    const char cell_column_result = cell_column(cell);
    const char cell_row_result = cell_row(cell);

    ASSERT_EQUAL(cell_column_result, 'g');
    ASSERT_EQUAL(cell_row_result, '2');
}