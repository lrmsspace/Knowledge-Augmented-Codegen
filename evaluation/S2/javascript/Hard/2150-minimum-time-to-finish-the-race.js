// Source: https://leetcode.com/problems/minimum-time-to-finish-the-race/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array tires where tires[i] = [fi, ri] indicates that the ith tire can finish its xth successive lap in fi * ri(x-1) seconds.
//
//
// 	For example, if fi = 3 and ri = 2, then the tire would finish its 1st lap in 3 seconds, its 2nd lap in 3 * 2 = 6 seconds, its 3rd lap in 3 * 22 = 12 seconds, etc.
//
//
// You are also given an integer changeTime and an integer numLaps.
//
// The race consists of numLaps laps and you may start the race with any tire. You have an unlimited supply of each tire and after every lap, you may change to any given tire (including the current tire type) if you wait changeTime seconds.
//
// Return the minimum time to finish the race.
//
// Example:
// Input: tires = [[2,3],[3,4]], changeTime = 5, numLaps = 4
// Output: 21
// Explanation: 
// Lap 1: Start with tire 0 and finish the lap in 2 seconds.
// Lap 2: Continue with tire 0 and finish the lap in 2 * 3 = 6 seconds.
// Lap 3: Change tires to a new tire 0 for 5 seconds and then finish the lap in another 2 seconds.
// Lap 4: Continue with tire 0 and finish the lap in 2 * 3 = 6 seconds.
// Total time = 2 + 6 + 5 + 2 + 6 = 21 seconds.
// The minimum time to complete the race is 21 seconds.
//
// Constraints:
// 1 <= tires.length <= 105
// 	tires[i].length == 2
// 	1 <= fi, changeTime <= 105
// 	2 <= ri <= 105
// 	1 <= numLaps <= 1000
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
 * @param {number[][]} tires
 * @param {number} changeTime
 * @param {number} numLaps
 * @return {number}
 */
var minimumFinishTime = function(tires, changeTime, numLaps) {
    const maxLaps = Math.min(numLaps, 20);
    const dp = new Array(maxLaps + 1).fill(Infinity);
    
    // Precompute minimum time to complete i laps without changing tires
    for (let i = 1; i <= maxLaps; i++) {
        for (const [f, r] of tires) {
            if (i === 1) {
                dp[i] = Math.min(dp[i], f);
            } else {
                const time = f * Math.pow(r, i - 1);
                if (time > dp[i - 1]) break;
                dp[i] = Math.min(dp[i], dp[i - 1] + time);
            }
        }
    }

    // Dynamic programming to find minimum time with tire changes
    for (let i = 1; i <= numLaps; i++) {
        for (let j = 1; j <= Math.min(i, maxLaps); j++) {
            if (i - j >= 0) {
                dp[i] = Math.min(dp[i], dp[j] + changeTime + dp[i - j]);
            }
        }
    }

    return dp[numLaps];
};
