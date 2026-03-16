// Source: https://leetcode.com/problems/check-if-every-row-and-column-contains-all-numbers/   |   Difficulty: Easy
//
// Problem Description:
// An n x n matrix is valid if every row and every column contains all the integers from 1 to n (inclusive).
//
// Given an n x n integer matrix matrix, return true if the matrix is valid. Otherwise, return false.
//
// Example:
// Input: matrix = [[1,2,3],[3,1,2],[2,3,1]]
// Output: true
// Explanation: In this case, n = 3, and every row and column contains the numbers 1, 2, and 3.
// Hence, we return true.
//
// Constraints:
// n == matrix.length == matrix[i].length
// 	1 <= n <= 100
// 	1 <= matrix[i][j] <= n
//

bool checkValid(int** matrix, int matrixSize, int* matrixColSize) {
    int n = matrixSize;
    int *row_check = (int *)malloc((n + 1) * sizeof(int));
    int *col_check = (int *)malloc((n + 1) * sizeof(int));

    for (int i = 0; i < n; i++) {
        // Reset check arrays for each row and column
        for (int k = 1; k <= n; k++) {
            row_check[k] = 0;
            col_check[k] = 0;
        }

        for (int j = 0; j < n; j++) {
            int row_val = matrix[i][j];
            int col_val = matrix[j][i];

            // Check row
            if (row_val < 1 || row_val > n || row_check[row_val]) {
                free(row_check);
                free(col_check);
                return false;
            }
            row_check[row_val] = 1;

            // Check column
            if (col_val < 1 || col_val > n || col_check[col_val]) {
                free(row_check);
                free(col_check);
                return false;
            }
            col_check[col_val] = 1;
        }
    }

    free(row_check);
    free(col_check);
    return true;        
}
