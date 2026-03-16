// Source: https://leetcode.com/problems/cyclically-rotating-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid​​​, where m and n are both even integers, and an integer k.
//
// The matrix is composed of several layers, which is shown in the below image, where each color is its own layer:
//
//
//
// A cyclic rotation of the matrix is done by cyclically rotating each layer in the matrix. To cyclically rotate a layer once, each element in the layer will take the place of the adjacent element in the counter-clockwise direction. An example rotation is shown below:
//
// Return the matrix after applying k cyclic rotations to it.
//
// Example:
// Input: grid = [[40,10],[30,20]], k = 1
// Output: [[10,20],[40,30]]
// Explanation: The figures above represent the grid at every state.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 50
// 	Both m and n are even integers.
// 	1 <= grid[i][j] <= 5000
// 	1 <= k <= 109
//

/**

 * Return an array of arrays of size *returnSize.

 * The sizes of the arrays are returned as *returnColumnSizes array.

 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().

 */

int** rotateGrid(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes){


    int m = gridSize, n = gridColSize[0];
    int layers = (m < n ? m : n) / 2;
    int** res = (int**)malloc(sizeof(int*) * m);
    *returnColumnSizes = (int*)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) {
        res[i] = (int*)malloc(sizeof(int) * n);
        (*returnColumnSizes)[i] = n;
    }
    *returnSize = m;

    for (int layer = 0; layer < layers; layer++) {
        int top = layer, bottom = m - layer - 1;
        int left = layer, right = n - layer - 1;
        int perimeter = 2 * (bottom - top + right - left);
        int rot = k % perimeter;

        // Copy the layer into a temporary array
        int* temp = (int*)malloc(sizeof(int) * perimeter);
        int idx = 0;

        // Top row
        for (int j = left; j <= right; j++) {
            temp[idx++] = grid[top][j];
        }
        // Right column
        for (int i = top + 1; i <= bottom; i++) {
            temp[idx++] = grid[i][right];
        }
        // Bottom row
        for (int j = right - 1; j >= left; j--) {
            temp[idx++] = grid[bottom][j];
        }
        // Left column
        for (int i = bottom - 1; i > top; i--) {
            temp[idx++] = grid[i][left];
        }

        // Rotate and place back into result
        idx = 0;
        // Top row
        for (int j = left; j <= right; j++) {
            res[top][j] = temp[(idx + rot) % perimeter];
            idx++;
        }
        // Right column
        for (int i = top + 1; i <= bottom; i++) {
            res[i][right] = temp[(idx + rot) % perimeter];
            idx++;
        }
        // Bottom row
        for (int j = right - 1; j >= left; j--) {
            res[bottom][j] = temp[(idx + rot) % perimeter];
            idx++;
        }
        // Left column
        for (int i = bottom - 1; i > top; i--) {
            res[i][left] = temp[(idx + rot) % perimeter];
            idx++;
        }
        free(temp);

}
    return res;
}