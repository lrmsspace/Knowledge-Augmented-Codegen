// Source: https://leetcode.com/problems/maximum-containers-on-a-ship/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer n representing an n x n cargo deck on a ship. Each cell on the deck can hold one container with a weight of exactly w.
//
// However, the total weight of all containers, if loaded onto the deck, must not exceed the ship's maximum weight capacity, maxWeight.
//
// Return the maximum number of containers that can be loaded onto the ship.
//
// Example:
// Input: n = 2, w = 3, maxWeight = 15
//
// Output: 4
//
// Explanation: 
//
// The deck has 4 cells, and each container weighs 3. The total weight of loading all containers is 12, which does not exceed maxWeight.
//
// Constraints:
// 1 <= n <= 1000
// 	1 <= w <= 1000
// 	1 <= maxWeight <= 109
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
 * @param {number} n
 * @param {number} w
 * @param {number} maxWeight
 * @return {number}
 */
var maxContainers = function(n, w, maxWeight) {
    const totalContainers = n * n;
    const totalWeight = totalContainers * w;
    return totalWeight <= maxWeight ? totalContainers : Math.floor(maxWeight / w);
};
