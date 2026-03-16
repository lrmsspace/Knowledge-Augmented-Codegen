// Source: https://leetcode.com/problems/zigzag-grid-traversal-with-skip/   |   Difficulty: Easy
//
// Problem Description:
// You are given an m x n 2D array grid of positive integers.
//
// Your task is to traverse grid in a zigzag pattern while skipping every alternate cell.
//
// Zigzag pattern traversal is defined as following the below actions:
//
//
// 	Start at the top-left cell (0, 0).
// 	Move right within a row until the end of the row is reached.
// 	Drop down to the next row, then traverse left until the beginning of the row is reached.
// 	Continue alternating between right and left traversal until every row has been traversed.
//
//
// Note that you must skip every alternate cell during the traversal.
//
// Return an array of integers result containing, in order, the value of the cells visited during the zigzag traversal with skips.
//
// Example:
// Input: grid = [[1,2],[3,4]]
//
// Output: [1,4]
//
// Explanation:
//
// Constraints:
// 2 <= n == grid.length <= 50
// 	2 <= m == grid[i].length <= 50
// 	1 <= grid[i][j] <= 2500
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* zigzagTraversal(int** grid, int gridSize, int* gridColSize, int* returnSize) {
    int m = gridSize;
    int n = gridColSize[0];
    int totalCells = m * n;
    int maxVisitedCells = (totalCells + 1) / 2; // Since we skip every alternate cell
    int* result = (int*)malloc(maxVisitedCells * sizeof(int));
    int index = 0;

    for (int i = 0; i < m; i++) {
        if (i % 2 == 0) { // Left to Right
            for (int j = 0; j < n; j += 2) {
                result[index++] = grid[i][j];
            }
        } else { // Right to Left
            for (int j = n - 1; j >= 0; j -= 2) {
                result[index++] = grid[i][j];
            }
        }
    }

    *returnSize = index;
    return result;      
}
