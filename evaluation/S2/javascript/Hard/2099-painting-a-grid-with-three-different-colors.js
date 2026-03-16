// Source: https://leetcode.com/problems/painting-a-grid-with-three-different-colors/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers m and n. Consider an m x n grid where each cell is initially white. You can paint each cell red, green, or blue. All cells must be painted.
//
// Return the number of ways to color the grid with no two adjacent cells having the same color. Since the answer can be very large, return it modulo 109 + 7.
//
// Example:
// Input: m = 1, n = 1
// Output: 3
// Explanation: The three possible colorings are shown in the image above.
//
// Constraints:
// 1 <= m <= 5
// 	1 <= n <= 1000
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
 * @param {number} m
 * @param {number} n
 * @return {number}
 */
var colorTheGrid = function(m, n) {
    const MOD = 1e9 + 7;
    const colors = [0, 1, 2];
    const validRows = [];
    
    function generateValidRows(row = []) {
        if (row.length === m) {
            validRows.push(row);
            return;
        }
        for (const color of colors) {
            if (row.length > 0 && row[row.length - 1] === color) continue;
            generateValidRows([...row, color]);
        }
    }
    
    generateValidRows();
    
    const dp = new Map();
    
    function isValidTransition(row1, row2) {
        for (let i = 0; i < m; i++) {
            if (row1[i] === row2[i]) return false;
        }
        return true;
    }
    
    function countWays(col = 0, prevRow = null) {
        if (col === n) return 1;
        const key = `${col}-${prevRow}`;
        if (dp.has(key)) return dp.get(key);
        
        let totalWays = 0;
        for (const row of validRows) {
            if (prevRow && !isValidTransition(prevRow, row)) continue;
            totalWays = (totalWays + countWays(col + 1, row)) % MOD;
        }
        
        dp.set(key, totalWays);
        return totalWays;
    }
    
    return countWays();
};
