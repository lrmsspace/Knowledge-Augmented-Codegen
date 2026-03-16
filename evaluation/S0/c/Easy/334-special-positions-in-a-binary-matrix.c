// Source: https://leetcode.com/problems/special-positions-in-a-binary-matrix/   |   Difficulty: Easy
//
// Problem Description:
// Given an m x n binary matrix mat, return the number of special positions in mat.
//
// A position (i, j) is called special if mat[i][j] == 1 and all other elements in row i and column j are 0 (rows and columns are 0-indexed).
//
// Example:
// Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
// Output: 1
// Explanation: (1, 2) is a special position because mat[1][2] == 1 and all other elements in row 1 and column 2 are 0.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 100
// 	mat[i][j] is either 0 or 1.
//

int numSpecial(int** mat, int matSize, int* matColSize) {
    int rows[100] = {0};
    int cols[100] = {0};
    int specialCount = 0;

    // First pass: Count the number of 1s in each row and column
    for (int i = 0; i < matSize; i++) {
        for (int j = 0; j < matColSize[i]; j++) {
            if (mat[i][j] == 1) {
                rows[i]++;
                cols[j]++;
            }
        }
    }

    // Second pass: Identify special positions
    for (int i = 0; i < matSize; i++) {
        for (int j = 0; j < matColSize[i]; j++) {
            if (mat[i][j] == 1 && rows[i] == 1 && cols[j] == 1) {
                specialCount++;
            }
        }
    }

    return specialCount;        
}
