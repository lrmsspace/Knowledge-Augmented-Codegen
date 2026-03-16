// Source: https://leetcode.com/problems/largest-divisible-subset/   |   Difficulty: Medium
//
// Problem Description:
// Given a set of distinct positive integers nums, return the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies:
//
//
// 	answer[i] % answer[j] == 0, or
// 	answer[j] % answer[i] == 0
//
//
// If there are multiple solutions, return any of them.
//
// Example:
// Input: nums = [1,2,3]
// Output: [1,2]
// Explanation: [1,3] is also accepted.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 2 * 109
// 	All the integers in nums are unique.
//

/**
 * @param {number[]} nums
 * @return {number[]}
 */
var largestDivisibleSubset = function(nums) {
    nums.sort((a, b) => a - b);
    const n = nums.length;
    const dp = new Array(n).fill(1);
    const prev = new Array(n).fill(-1);
    let maxSize = 0;
    let maxIndex = -1;

    for (let i = 1; i < n; i++) {
        for (let j = 0; j < i; j++) {
            if (nums[i] % nums[j] === 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > maxSize) {
            maxSize = dp[i];
            maxIndex = i;
        }
    }

    const result = [];
    while (maxIndex !== -1) {
        result.push(nums[maxIndex]);
        maxIndex = prev[maxIndex];
    }

    return result.reverse();
};