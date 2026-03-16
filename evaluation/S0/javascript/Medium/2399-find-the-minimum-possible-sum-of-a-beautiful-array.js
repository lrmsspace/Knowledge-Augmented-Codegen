// Source: https://leetcode.com/problems/find-the-minimum-possible-sum-of-a-beautiful-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given positive integers n and target.
//
// An array nums is beautiful if it meets the following conditions:
//
//
// 	nums.length == n.
// 	nums consists of pairwise distinct positive integers.
// 	There doesn't exist two distinct indices, i and j, in the range [0, n - 1], such that nums[i] + nums[j] == target.
//
//
// Return the minimum possible sum that a beautiful array could have modulo 109 + 7.
//
// Example:
// Input: n = 2, target = 3
// Output: 4
// Explanation: We can see that nums = [1,3] is beautiful.
// - The array nums has length n = 2.
// - The array nums consists of pairwise distinct positive integers.
// - There doesn't exist two distinct indices, i and j, with nums[i] + nums[j] == 3.
// It can be proven that 4 is the minimum possible sum that a beautiful array could have.
//
// Constraints:
// 1 <= n <= 109
// 	1 <= target <= 109
//

/**
 * @param {number} n
 * @param {number} target
 * @return {number}
 */
var minimumPossibleSum = function(n, target) {
    const MOD = 1e9 + 7;
    let sum = 0;
    let count = 0;
    let num = 1;
    const used = new Set();
    while (count < n) {
        if (!used.has(target - num)) {
            used.add(num);
            sum = (sum + num) % MOD;
            count++;
        }
        num++;
    }
    return sum;
};