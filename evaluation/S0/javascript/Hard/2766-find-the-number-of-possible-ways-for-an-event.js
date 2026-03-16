// Source: https://leetcode.com/problems/find-the-number-of-possible-ways-for-an-event/   |   Difficulty: Hard
//
// Problem Description:
// You are given three integers n, x, and y.
//
// An event is being held for n performers. When a performer arrives, they are assigned to one of the x stages. All performers assigned to the same stage will perform together as a band, though some stages might remain empty.
//
// After all performances are completed, the jury will award each band a score in the range [1, y].
//
// Return the total number of possible ways the event can take place.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Note that two events are considered to have been held differently if either of the following conditions is satisfied:
//
//
// 	Any performer is assigned a different stage.
// 	Any band is awarded a different score.
//
// Example:
// Input: n = 1, x = 2, y = 3
//
// Output: 6
//
// Explanation:
//
//
// 	There are 2 ways to assign a stage to the performer.
// 	The jury can award a score of either 1, 2, or 3 to the only band.
//
// Constraints:
// 1 <= n, x, y <= 1000
//

/**
 * @param {number} n
 * @param {number} x
 * @param {number} y
 * @return {number}
 */
var numberOfWays = function(n, x, y) {
    const MOD = 1e9 + 7;
    const stirling = Array.from({ length: n + 1 }, () => Array(n + 1).fill(0));
    stirling[0][0] = 1;
    for (let i = 1; i <= n; i++) {
        for (let j = 1; j <= i; j++) {
            stirling[i][j] = (stirling[i - 1][j - 1] + (j * stirling[i - 1][j]) % MOD) % MOD;
        }
    }
    let result = 0;
    for (let k = 1; k <= Math.min(n, x); k++) {
        const waysToAssignStages = stirling[n][k];
        const waysToChooseStages = combination(x, k, MOD);
        const waysToAwardScores = modPow(y, k, MOD);
        result = (result + (((waysToAssignStages * waysToChooseStages) % MOD) * waysToAwardScores) % MOD) % MOD;
    }
    return result;  
};
