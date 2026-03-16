// Source: https://leetcode.com/problems/largest-submatrix-with-rearrangements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns of the matrix in any order.
//
// Return the area of the largest submatrix within matrix where every element of the submatrix is 1 after reordering the columns optimally.
//
// Example:
// Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
// Output: 4
// Explanation: You can rearrange the columns as shown above.
// The largest submatrix of 1s, in bold, has an area of 4.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m * n <= 105
// 	matrix[i][j] is either 0 or 1.
//

int largestSubmatrix(int** matrix, int matrixSize, int* matrixColSize) {
    int m = matrixSize;
    int n = matrixColSize[0];
    int heights[m][n];
    memset(heights, 0, sizeof(heights));

    for (int j = 0; j < n; j++) {
        heights[0][j] = matrix[0][j];
        for (int i = 1; i < m; i++) {
            if (matrix[i][j] == 1) {
                heights[i][j] = heights[i - 1][j] + 1;
            } else {
                heights[i][j] = 0;
            }
        }
    }

    int maxArea = 0;
    for (int i = 0; i < m; i++) {
        int count[n + 1];
        memset(count, 0, sizeof(count));
        for (int j = 0; j < n; j++) {
            count[heights[i][j]]++;
        }

        int colIndex = 0;
        for (int h = n; h >= 1; h--) {
            while (count[h] > 0) {
                int area = h * (colIndex + 1);
                if (area > maxArea) {
                    maxArea = area;
                }
                colIndex++;
                count[h]--;
            }
        }
    }

    return maxArea;     
}
