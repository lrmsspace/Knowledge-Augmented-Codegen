// Source: https://leetcode.com/problems/find-kth-largest-xor-coordinate-value/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D matrix of size m x n, consisting of non-negative integers. You are also given an integer k.
//
// The value of coordinate (a, b) of the matrix is the XOR of all matrix[i][j] where 0 <= i <= a < m and 0 <= j <= b < n (0-indexed).
//
// Find the kth largest value (1-indexed) of all the coordinates of matrix.
//
// Example:
// Input: matrix = [[5,2],[1,6]], k = 1
// Output: 7
// Explanation: The value of coordinate (0,1) is 5 XOR 2 = 7, which is the largest value.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 1000
// 	0 <= matrix[i][j] <= 106
// 	1 <= k <= m * n
//

/**
 * @param {number[][]} matrix
 * @param {number} k
 * @return {number}
 */
var kthLargestValue = function(matrix, k) {
    const m = matrix.length;
    const n = matrix[0].length;
    const xorMatrix = Array.from({ length: m + 1 }, () => Array(n + 1).fill(0));
    const xorValues = [];  
    for (let i = 1; i <= m; i++) {      
        for (let j = 1; j <= n; j++) {  
            xorMatrix[i][j] = xorMatrix[i - 1][j] ^ xorMatrix[i][j - 1] ^ xorMatrix[i - 1][j - 1] ^ matrix[i - 1][j - 1];
            xorValues.push(xorMatrix[i][j]);
        }
    }
    xorValues.sort((a, b) => b - a);  
    return xorValues[k - 1];    
};
