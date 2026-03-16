// Source: https://leetcode.com/problems/increment-submatrices-by-one/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n, indicating that we initially have an n x n 0-indexed integer matrix mat filled with zeroes.
//
// You are also given a 2D integer array query. For each query[i] = [row1i, col1i, row2i, col2i], you should do the following operation:
//
//
// 	Add 1 to every element in the submatrix with the top left corner (row1i, col1i) and the bottom right corner (row2i, col2i). That is, add 1 to mat[x][y] for all row1i <= x <= row2i and col1i <= y <= col2i.
//
//
// Return the matrix mat after performing every query.
//
// Example:
// Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
// Output: [[1,1,0],[1,2,1],[0,1,1]]
// Explanation: The diagram above shows the initial matrix, the matrix after the first query, and the matrix after the second query.
// - In the first query, we add 1 to every element in the submatrix with the top left corner (1, 1) and bottom right corner (2, 2).
// - In the second query, we add 1 to every element in the submatrix with the top left corner (0, 0) and bottom right corner (1, 1).
//
// Constraints:
// 1 <= n <= 500
// 	1 <= queries.length <= 104
// 	0 <= row1i <= row2i < n
// 	0 <= col1i <= col2i < n
//

/**
 * @param {number} n
 * @param {number[][]} queries
 * @return {number[][]}
 */
var rangeAddQueries = function(n, queries) {
    const mat = Array.from({ length: n }, () => new Array(n).fill(0));

    for (const [row1, col1, row2, col2] of queries) {
        for (let i = row1; i <= row2; i++) {
            for (let j = col1; j <= col2; j++) {
                mat[i][j]++;
            }
        }
    }
    return mat;
};