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
 * @param {number[][]} mat
 * @return {number[]}
 */
var findPeakGrid = function(mat) {
    const rows = mat.length;
    const cols = mat[0].length;
    let left = 0;
    let right = cols - 1;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        let maxRow = 0;
        for (let i = 1; i < rows; i++) {
            if (mat[i][mid] > mat[maxRow][mid]) {
                maxRow = i;
            }
        }
        const up = maxRow > 0 ? mat[maxRow - 1][mid] : -1;
        const down = maxRow < rows - 1 ? mat[maxRow + 1][mid] : -1;
        if (mat[maxRow][mid] > up && mat[maxRow][mid] > down) {
            return [maxRow, mid];
        } else if (mat[maxRow][mid] < down) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
};