// Source: https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n matrix matrix and an integer k, return the max sum of a rectangle in the matrix such that its sum is no larger than k.
//
// It is guaranteed that there will be a rectangle with a sum no larger than k.
//
// Example:
// Input: matrix = [[1,0,1],[0,-2,3]], k = 2
// Output: 2
// Explanation: Because the sum of the blue rectangle [[0, 1], [-2, 3]] is 2, and 2 is the max number no larger than k (k = 2).
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 100
// 	-100 <= matrix[i][j] <= 100
// 	-105 <= k <= 105
//
//
//  
// Follow up: What if the number of rows is much larger than the number of columns?
//

/**
 * @param {number[][]} matrix
 * @param {number} k
 * @return {number}
 */
var maxSumSubmatrix = function(matrix, k) {
    const m = matrix.length;
    const n = matrix[0].length;
    let maxPointsOnLine = -Infinity;
    for (let left = 0; left < n; left++) {
        const rowSums = new Array(m).fill(0);
        for (let right = left; right < n; right++) {
            for (let i = 0; i < m; i++) {
                rowSums[i] += matrix[i][right];
            }
            const set = new Set([0]);
            let currentMax = -Infinity;
            let cumulativeSum = 0;
            for (let sum of rowSums) {
                cumulativeSum += sum;
                for (let prevSum of set) {
                    if (cumulativeSum - prevSum <= k) {
                        currentMax = Math.max(currentMax, cumulativeSum - prevSum);
                    }
                }
                set.add(cumulativeSum);
            }
            maxPointsOnLine = Math.max(maxPointsOnLine, currentMax);
        }
    }
    return maxPointsOnLine;
        
};
