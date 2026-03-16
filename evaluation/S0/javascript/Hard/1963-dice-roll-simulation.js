// Source: https://leetcode.com/problems/dice-roll-simulation/   |   Difficulty: Hard
//
// Problem Description:
// A die simulator generates a random number from 1 to 6 for each roll. You introduced a constraint to the generator such that it cannot roll the number i more than rollMax[i] (1-indexed) consecutive times.
//
// Given an array of integers rollMax and an integer n, return the number of distinct sequences that can be obtained with exact n rolls. Since the answer may be too large, return it modulo 109 + 7.
//
// Two sequences are considered different if at least one element differs from each other.
//
// Example:
// Input: n = 2, rollMax = [1,1,2,2,2,3]
// Output: 34
// Explanation: There will be 2 rolls of die, if there are no constraints on the die, there are 6 * 6 = 36 possible combinations. In this case, looking at rollMax array, the numbers 1 and 2 appear at most once consecutively, therefore sequences (1,1) and (2,2) cannot occur, so the final answer is 36-2 = 34.
//
// Constraints:
// 1 <= n <= 5000
// 	rollMax.length == 6
// 	1 <= rollMax[i] <= 15
//

/**
 * @param {number} n
 * @param {number[]} rollMax
 * @return {number}
 */
var dieSimulator = function(n, rollMax) {
    const MOD = 1e9 + 7;
    const dp = Array.from({ length: n }, () => new Array(6).fill(0));
    for (let i = 0; i < 6; i++) {
        dp[0][i] = 1;
    }

    for (let i = 1; i < n; i++) {
        for (let j = 0; j < 6; j++) {
            dp[i][j] = 0;
            for (let k = 0; k < 6; k++) {
                if (j === k) {
                    let count = 1;
                    while (count <= rollMax[j] && i - count >= 0 && dp[i - count][j] > 0) {
                        dp[i][j] = (dp[i][j] + dp[i - count][j]) % MOD;
                        count++;
                    }
                } else {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
                }
            }
        }
    }
    let total = 0;
    for (let i = 0; i < 6; i++) {
        total = (total + dp[n - 1][i]) % MOD;
    }
    return total;

};
