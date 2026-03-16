// Source: https://leetcode.com/problems/maximum-sum-with-at-most-k-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer matrix grid of size n x m, an integer array limits of length n, and an integer k. The task is to find the maximum sum of at most k elements from the matrix grid such that:
//
//
// 	
// 	The number of elements taken from the ith row of grid does not exceed limits[i].
// 	
//
//
// Return the maximum sum.
//
// Example:
// Input: grid = [[1,2],[3,4]], limits = [1,2], k = 2
//
// Output: 7
//
// Explanation:
//
//
// 	From the second row, we can take at most 2 elements. The elements taken are 4 and 3.
// 	The maximum possible sum of at most 2 selected elements is 4 + 3 = 7.
//
// Constraints:
// n == grid.length == limits.length
// 	m == grid[i].length
// 	1 <= n, m <= 500
// 	0 <= grid[i][j] <= 105
// 	0 <= limits[i] <= m
// 	0 <= k <= min(n * m, sum(limits))
//

/**
 * @param {number[][]} grid
 * @param {number[]} limits
 * @param {number} k
 * @return {number}
 */
var maxSum = function(grid, limits, k) {
    const n = grid.length;
    const m = grid[0].length;
    const elements = [];
    for (let i = 0; i < n; i++) {
        const row = grid[i].slice().sort((a, b) => b - a);
        for (let j = 0; j < limits[i]; j++) {
            if (j < row.length) {
                elements.push(row[j]);
            }                               
        }
    }
    elements.sort((a, b) => b - a);
    let totalSum = 0;
    for (let i = 0; i < Math.min(k, elements.length); i++) {
        totalSum += elements[i];
    }
    return totalSum;    
};
