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

/**
 * @param {number[][]} matrix
 * @return {boolean}
 */
var checkValid = function(matrix) {
    const n = matrix.length;
    const expectedSet = new Set();
    for (let i = 1; i <= n; i++) {
        expectedSet.add(i);
    }

    for (let i = 0; i < n; i++) {
        const rowSet = new Set();
        const colSet = new Set();
        for (let j = 0; j < n; j++) {
            rowSet.add(matrix[i][j]);
            colSet.add(matrix[j][i]);
        }
        if (rowSet.size !== n || colSet.size !== n) {
            return false;
        }
        for (let num of expectedSet) {
            if (!rowSet.has(num) || !colSet.has(num)) {
                return false;
            }
        }
    }
    return true;
};