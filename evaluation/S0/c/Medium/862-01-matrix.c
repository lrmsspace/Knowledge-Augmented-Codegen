// Source: https://leetcode.com/problems/01-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
//
// The distance between two cells sharing a common edge is 1.
//
// Example:
// Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
// Output: [[0,0,0],[0,1,0],[0,0,0]]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 104
// 	1 <= m * n <= 104
// 	mat[i][j] is either 0 or 1.
// 	There is at least one 0 in mat.
//
//
//  
// Note: This question is the same as 1765: https://leetcode.com/problems/map-of-highest-peak/
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** updateMatrix(int** mat, int matSize, int* matColSize, int* returnSize, int** returnColumnSizes) {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int rows = matSize;
    int cols = matColSize[0];
    
    int** dist = (int**)malloc(rows * sizeof(int*));
    *returnColumnSizes = (int*)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++) {
        dist[i] = (int*)malloc(cols * sizeof(int));
        (*returnColumnSizes)[i] = cols;
        for (int j = 0; j < cols; j++) {
            dist[i][j] = (mat[i][j] == 0) ? 0 : 10000; // Use a large number for initial distance
        }
    }
    
    // First pass: top-left to bottom-right
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] == 1) {
                if (i > 0) {
                    dist[i][j] = fmin(dist[i][j], dist[i - 1][j] + 1);
                }
                if (j > 0) {
                    dist[i][j] = fmin(dist[i][j], dist[i][j - 1] + 1);
                }
            }
        }
    }
    
    // Second pass: bottom-right to top-left
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = cols - 1; j >= 0; j--) {
            if (mat[i][j] == 1) {
                if (i < rows - 1) {
                    dist[i][j] = fmin(dist[i][j], dist[i + 1][j] + 1);
                }
                if (j < cols - 1) {
                    dist[i][j] = fmin(dist[i][j], dist[i][j + 1] + 1);
                }
            }
        }
    }
    
    *returnSize = rows;
    return dist;        
}
