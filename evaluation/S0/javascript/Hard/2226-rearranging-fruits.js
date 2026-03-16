// Source: https://leetcode.com/problems/rearranging-fruits/   |   Difficulty: Hard
//
// Problem Description:
// You have two fruit baskets containing n fruits each. You are given two 0-indexed integer arrays basket1 and basket2 representing the cost of fruit in each basket. You want to make both baskets equal. To do so, you can use the following operation as many times as you want:
//
//
// 	Choose two indices i and j, and swap the ith fruit of basket1 with the jth fruit of basket2.
// 	The cost of the swap is min(basket1[i], basket2[j]).
//
//
// Two baskets are considered equal if sorting them according to the fruit cost makes them exactly the same baskets.
//
// Return the minimum cost to make both the baskets equal or -1 if impossible.
//
// Example:
// Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
// Output: 1
// Explanation: Swap index 1 of basket1 with index 0 of basket2, which has cost 1. Now basket1 = [4,1,2,2] and basket2 = [2,4,1,2]. Rearranging both the arrays makes them equal.
//
// Constraints:
// basket1.length == basket2.length
// 	1 <= basket1.length <= 105
// 	1 <= basket1[i], basket2[i] <= 109
//

/**
 * @param {number[]} basket1
 * @param {number[]} basket2
 * @return {number}
 */
var minCost = function(basket1, basket2) {
    const n = basket1.length;
    const count = new Map();
    let minCost = Infinity;
    for (let i = 0; i < n; i++) {
        count.set(basket1[i], (count.get(basket1[i]) || 0) + 1);
        count.set(basket2[i], (count.get(basket2[i]) || 0) - 1);
        minCost = Math.min(minCost, basket1[i], basket2[i]);
    }
    let totalCost = 0;
    for (const [fruit, freq] of count.entries()) {
        if (freq % 2 !== 0) {
            return -1;
        }
        if (freq > 0) {
            totalCost += Math.min(fruit, 2 * minCost) * (freq / 2);
        }
    }
    return totalCost;
};
