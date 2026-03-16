// Source: https://leetcode.com/problems/spiral-matrix-iii/   |   Difficulty: Medium
//
// Problem Description:
// You start at the cell (rStart, cStart) of an rows x cols grid facing east. The northwest corner is at the first row and column in the grid, and the southeast corner is at the last row and column.
//
// You will walk in a clockwise spiral shape to visit every position in this grid. Whenever you move outside the grid's boundary, we continue our walk outside the grid (but may return to the grid boundary later.). Eventually, we reach all rows * cols spaces of the grid.
//
// Return an array of coordinates representing the positions of the grid in the order you visited them.
//
// Example:
// Input: rows = 1, cols = 4, rStart = 0, cStart = 0
// Output: [[0,0],[0,1],[0,2],[0,3]]
//
// Constraints:
// 1 <= rows, cols <= 100
// 	0 <= rStart < rows
// 	0 <= cStart < cols
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** spiralMatrixIII(int rows, int cols, int rStart, int cStart, int* returnSize, int** returnColumnSizes) {
    int total = rows * cols;
    int **result = (int **)malloc(sizeof(int *) * total);
    *returnColumnSizes = (int *)malloc(sizeof(int) * total);
    *returnSize = 0;

    int directions[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}}; // right, down, left, up
    int dirIndex = 0; // start moving right
    int steps = 1; // initial step size
    int r = rStart, c = cStart;

    result[(*returnSize)] = (int *)malloc(sizeof(int) * 2);
    result[(*returnSize)][0] = r;
    result[(*returnSize)][1] = c;
    (*returnColumnSizes)[(*returnSize)] = 2;
    (*returnSize)++;

    while (*returnSize < total) {
        for (int i = 0; i < 2; i++) { // two times for each step size
            for (int j = 0; j < steps; j++) {
                r += directions[dirIndex][0];
                c += directions[dirIndex][1];

                if (r >= 0 && r < rows && c >= 0 && c < cols) {
                    result[(*returnSize)] = (int *)malloc(sizeof(int) * 2);
                    result[(*returnSize)][0] = r;
                    result[(*returnSize)][1] = c;
                    (*returnColumnSizes)[(*returnSize)] = 2;
                    (*returnSize)++;
                }
            }
            dirIndex = (dirIndex + 1) % 4; // change direction
        }
        steps++; // increase step size after completing two directions
    }

    return result;      
}
