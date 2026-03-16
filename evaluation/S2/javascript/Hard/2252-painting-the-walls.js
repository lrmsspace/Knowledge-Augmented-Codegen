// Source: https://leetcode.com/problems/painting-the-walls/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays, cost and time, of size n representing the costs and the time taken to paint n different walls respectively. There are two painters available:
//
//
// 	A paid painter that paints the ith wall in time[i] units of time and takes cost[i] units of money.
// 	A free painter that paints any wall in 1 unit of time at a cost of 0. But the free painter can only be used if the paid painter is already occupied.
//
//
// Return the minimum amount of money required to paint the n walls.
//
// Example:
// Input: cost = [1,2,3,2], time = [1,2,3,2]
// Output: 3
// Explanation: The walls at index 0 and 1 will be painted by the paid painter, and it will take 3 units of time; meanwhile, the free painter will paint the walls at index 2 and 3, free of cost in 2 units of time. Thus, the total cost is 1 + 2 = 3.
//
// Constraints:
// 1 <= cost.length <= 500
// 	cost.length == time.length
// 	1 <= cost[i] <= 106
// 	1 <= time[i] <= 500
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
 * @param {number[]} cost
 * @param {number[]} time
 * @return {number}
 */
var paintWalls = function(cost, time) {
    const n = cost.length;
    const dp = Array(n + 1).fill(Infinity);
    dp[0] = 0;
    
    for (let i = 1; i <= n; i++) {
        for (let j = 0; j < i; j++) {
            const paidTime = time[i - 1];
            const freeTime = i - j - 1;
            if (paidTime >= freeTime) {
                dp[i] = Math.min(dp[i], dp[j] + cost[i - 1]);
            }
        }
    }
    
    return dp[n];
};
