// Source: https://leetcode.com/problems/min-cost-climbing-stairs/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.
//
// You can either start from the step with index 0, or the step with index 1.
//
// Return the minimum cost to reach the top of the floor.
//
// Example:
// Input: cost = [10,15,20]
// Output: 15
// Explanation: You will start at index 1.
// - Pay 15 and climb two steps to reach the top.
// The total cost is 15.
//
// Constraints:
// 2 <= cost.length <= 1000
// 	0 <= cost[i] <= 999
//

/**
 * @param {number[]} cost
 * @return {number}
 */
var minCostClimbingStairs = function(cost) {
    const n = cost.length;
    let first = cost[0];
    let second = cost[1];
    for (let i = 2; i < n; i++) {
        const current = cost[i] + Math.min(first, second);
        first = second;
        second = current;
    }
    return Math.min(first, second);
};
