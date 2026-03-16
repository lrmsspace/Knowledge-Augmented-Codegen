// Source: https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/   |   Difficulty: Hard
//
// Problem Description:
// Given a matrix and a target, return the number of non-empty submatrices that sum to target.
//
// A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.
//
// Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.
//
// Example:
// Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
// Output: 4
// Explanation: The four 1x1 submatrices that only contain 0.
//
// Constraints:
// 1 <= matrix.length <= 100
// 	1 <= matrix[0].length <= 100
// 	-1000 <= matrix[i][j] <= 1000
// 	-10^8 <= target <= 10^8
//

/**
 * @param {number[][]} matrix
 * @param {number} target
 * @return {number}
 */
var numSubmatrixSumTarget = function(matrix, target) {
    const m = matrix.length;
    const n = matrix[0].length;
    let result = 0;
    for (let left = 0; left < n; left++) {
        const rowSums = new Array(m).fill(0);
        for (let right = left; right < n; right++) {
            for (let i = 0; i < m; i++) {
                rowSums[i] += matrix[i][right];
            }
            const count = new Map();
            count.set(0, 1);
            let currentSum = 0;
            for (const sum of rowSums) {
                currentSum += sum;
                if (count.has(currentSum - target)) {
                    result += count.get(currentSum - target);
                }
                count.set(currentSum, (count.get(currentSum) || 0) + 1);
            }
        }
    }
    return result;  
};
