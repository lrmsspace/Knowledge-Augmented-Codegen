// Source: https://leetcode.com/problems/cells-with-odd-values-in-a-matrix/   |   Difficulty: Easy
//
// Problem Description:
// There is an m x n matrix that is initialized to all 0's. There is also a 2D array indices where each indices[i] = [ri, ci] represents a 0-indexed location to perform some increment operations on the matrix.
//
// For each location indices[i], do both of the following:
//
//
// 	Increment all the cells on row ri.
// 	Increment all the cells on column ci.
//
//
// Given m, n, and indices, return the number of odd-valued cells in the matrix after applying the increment to all locations in indices.
//
// Example:
// Input: m = 2, n = 3, indices = [[0,1],[1,1]]
// Output: 6
// Explanation: Initial matrix = [[0,0,0],[0,0,0]].
// After applying first increment it becomes [[1,2,1],[0,1,0]].
// The final matrix is [[1,3,1],[1,3,1]], which contains 6 odd numbers.
//
// Constraints:
// 1 <= m, n <= 50
// 	1 <= indices.length <= 100
// 	0 <= ri < m
// 	0 <= ci < n
//
//
//  
// Follow up: Could you solve this in O(n + m + indices.length) time with only O(n + m) extra space?
//

/**
 * @param {number} m
 * @param {number} n
 * @param {number[][]} indices
 * @return {number}
 */
var oddCells = function(m, n, indices) {
    const rowIncrements = new Array(m).fill(0);
    const colIncrements = new Array(n).fill(0);
    for (const [ri, ci] of indices) {
        rowIncrements[ri]++;
        colIncrements[ci]++;
    }
    let oddCount = 0;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if ((rowIncrements[i] + colIncrements[j]) % 2 !== 0) {
                oddCount++;
            }
        }
    }
    return oddCount;
};