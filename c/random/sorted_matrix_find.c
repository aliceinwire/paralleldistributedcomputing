#include <stdio.h>

#define NUM 5
#define ROWS NUM
#define COLS NUM

void print_matrix(int matrix[ROWS][COLS], unsigned int n, 
		int hrow = -1, int hcol = -1)
{
    unsigned int row;
    unsigned int col;

    for (row = 0; row < n; ++row) {
        for (col = 0; col < n; ++col) {
            if (hrow == row && hcol == col)
                printf("*%d*|", matrix[row][col]);
            else
                printf(" %d |", matrix[row][col]);
        }
        printf("\n");
        for (col = 0; col < n-1; ++col) {
            printf("_____");
        }
        printf("_\n");
    }    
}

void find_in_matrix(int matrix[ROWS][COLS], int row, int col, int to_find)
{
    static unsigned int counter = 0;

    ++counter;
    if (row > ROWS-1 || col < 0) {
        printf("Not found in the matrix!\n");
        return;
    }
    if (matrix[row][col] == to_find) {
        printf("found (%d) at matrix[%d][%d] in %d comparisons:\n", 
            to_find, row, col, counter);
        print_matrix(matrix, NUM, row, col);
        counter = 0;
        return;
    }
    else if (matrix[row][col] > to_find)
        --col;
    else
        ++row;
    find_in_matrix(matrix, row, col, to_find);
}

int main()
{
    int matrix[ROWS][COLS] = { 
        {0, 3,  5,  6, 100},
        {1, 4,  7,  8, 101},
        {2, 9,  11, 12, 102},
        {10, 13, 14, 15, 103},
        {16, 17, 18, 19, 104}
    };

    print_matrix(matrix, NUM);
    find_in_matrix(matrix, 0, COLS-1, 6);
    find_in_matrix(matrix, 0, COLS-1, 0);
    find_in_matrix(matrix, 0, COLS-1, 3);
    find_in_matrix(matrix, 0, COLS-1, 5);
    find_in_matrix(matrix, 0, COLS-1, 19);
    find_in_matrix(matrix, 0, COLS-1, 14);
    find_in_matrix(matrix, 0, COLS-1, 104);
    return 0;
}
