// Source: https://leetcode.com/problems/find-a-peak-element-ii/   |   Difficulty: Medium
//
// Problem Description:
// A peak element in a 2D grid is an element that is strictly greater than all of its adjacent neighbors to the left, right, top, and bottom.
//
// Given a 0-indexed m x n matrix mat where no two adjacent cells are equal, find any peak element mat[i][j] and return the length 2 array [i,j].
//
// You may assume that the entire matrix is surrounded by an outer perimeter with the value -1 in each cell.
//
// You must write an algorithm that runs in O(m log(n)) or O(n log(m)) time.
//
// Example:
// Input: mat = [[1,4],[3,2]]
// Output: [0,1]
// Explanation: Both 3 and 4 are peak elements so [1,0] and [0,1] are both acceptable answers.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 500
// 	1 <= mat[i][j] <= 105
// 	No two adjacent cells are equal.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findPeakGrid(int** mat, int matSize, int* matColSize, int* returnSize) {
    int left = 0, right = matColSize[0] - 1;
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int maxRow = 0;

        // Find the row index of the maximum element in the mid column
        for (int i = 1; i < matSize; i++) {
            if (mat[i][mid] > mat[maxRow][mid]) {
                maxRow = i;
            }
        }

        // Check the neighbors
        int leftNeighbor = (mid - 1 >= 0) ? mat[maxRow][mid - 1] : -1;
        int rightNeighbor = (mid + 1 < matColSize[0]) ? mat[maxRow][mid + 1] : -1;

        if (mat[maxRow][mid] > leftNeighbor && mat[maxRow][mid] > rightNeighbor) {
            result[0] = maxRow;
            result[1] = mid;
            return result;
        } else if (leftNeighbor > mat[maxRow][mid]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result; // This line should never be reached     
}
