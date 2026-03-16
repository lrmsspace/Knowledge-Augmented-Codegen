// Source: https://leetcode.com/problems/count-submatrices-with-all-ones/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n binary matrix mat, return the number of submatrices that have all ones.
//
// Example:
// Input: mat = [[1,0,1],[1,1,0],[1,1,0]]
// Output: 13
// Explanation: 
// There are 6 rectangles of side 1x1.
// There are 2 rectangles of side 1x2.
// There are 3 rectangles of side 2x1.
// There is 1 rectangle of side 2x2. 
// There is 1 rectangle of side 3x1.
// Total number of rectangles = 6 + 2 + 3 + 1 + 1 = 13.
//
// Constraints:
// 1 <= m, n <= 150
// 	mat[i][j] is either 0 or 1.
//

int numSubmat(int** mat, int matSize, int* matColSize) {
    int m = matSize;
    int n = matColSize[0];
    int count = 0;

    // Preprocess the matrix to calculate the number of consecutive ones in each row
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (mat[i][j] == 1) {
                mat[i][j] += mat[i][j - 1];
            }
        }
    }

    // Count submatrices with all ones
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            int minWidth = mat[i][j];
            for (int k = i; k >= 0 && minWidth > 0; k--) {
                minWidth = (mat[k][j] < minWidth) ? mat[k][j] : minWidth;
                count += minWidth;
            }
        }
    }

    return count;       
}
