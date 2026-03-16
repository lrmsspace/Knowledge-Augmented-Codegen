// Source: https://leetcode.com/problems/search-a-2d-matrix/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix matrix with the following two properties:
//
//
// 	Each row is sorted in non-decreasing order.
// 	The first integer of each row is greater than the last integer of the previous row.
//
//
// Given an integer target, return true if target is in matrix or false otherwise.
//
// You must write a solution in O(log(m * n)) time complexity.
//
// Example:
// Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
// Output: true
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 100
// 	-104 <= matrix[i][j], target <= 104
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} matrix
 * @param {number} target
 * @return {boolean}
 */
var searchMatrix = function(matrix, target) {
    const m = matrix.length, n = matrix[0].length;
    let left = 0, right = m * n - 1;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        const row = Math.floor(mid / n), col = mid % n;
        const val = matrix[row][col];
        if (val === target) return true;
        if (val < target) left = mid + 1;
        else right = mid - 1;
    }
    return false;
};
