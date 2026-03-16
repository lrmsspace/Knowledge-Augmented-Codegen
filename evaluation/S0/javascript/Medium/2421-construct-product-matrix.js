// Source: https://leetcode.com/problems/construct-product-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given a 0-indexed 2D integer matrix grid of size n * m, we define a 0-indexed 2D matrix p of size n * m as the product matrix of grid if the following condition is met:
//
//
// 	Each element p[i][j] is calculated as the product of all elements in grid except for the element grid[i][j]. This product is then taken modulo 12345.
//
//
// Return the product matrix of grid.
//
// Example:
// Input: grid = [[1,2],[3,4]]
// Output: [[24,12],[8,6]]
// Explanation: p[0][0] = grid[0][1] * grid[1][0] * grid[1][1] = 2 * 3 * 4 = 24
// p[0][1] = grid[0][0] * grid[1][0] * grid[1][1] = 1 * 3 * 4 = 12
// p[1][0] = grid[0][0] * grid[0][1] * grid[1][1] = 1 * 2 * 4 = 8
// p[1][1] = grid[0][0] * grid[0][1] * grid[1][0] = 1 * 2 * 3 = 6
// So the answer is [[24,12],[8,6]].
//
// Constraints:
// 1 <= n == grid.length <= 105
// 	1 <= m == grid[i].length <= 105
// 	2 <= n * m <= 105
// 	1 <= grid[i][j] <= 109
//

/**
 * @param {number[][]} grid
 * @return {number[][]}
 */
var constructProductMatrix = function(grid) {
    const MOD = 12345;
    const n = grid.length;
    const m = grid[0].length;
    let totalProduct = 1;
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < m; j++) {
            totalProduct = (totalProduct * grid[i][j]) % MOD;
        }
    }
    const result = Array.from({ length: n }, () => Array(m).fill(0));
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < m; j++) {
            const inverse = modInverse(grid[i][j], MOD);
            result[i][j] = (totalProduct * inverse) % MOD;
        }
    }
    return result;
};

function modInverse(a, m) {
    let m0 = m;
    let y = 0, x = 1;
    if (m === 1) return 0;
    while (a > 1) {
        let q = Math.floor(a / m);
        let t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}