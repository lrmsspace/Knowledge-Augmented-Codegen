// Source: https://leetcode.com/problems/n-repeated-element-in-size-2n-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums with the following properties:
//
//
// 	nums.length == 2 * n.
// 	nums contains n + 1 unique elements.
// 	Exactly one element of nums is repeated n times.
//
//
// Return the element that is repeated n times.
//
// Example:
// Input: nums = [1,2,3,3]
// Output: 3
//
// Constraints:
// 2 <= n <= 5000
// 	nums.length == 2 * n
// 	0 <= nums[i] <= 104
// 	nums contains n + 1 unique elements and one of them is repeated exactly n times.
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
 * @param {number[]} nums
 * @return {number}
 */
var repeatedNTimes = function(nums) {
    const seen = new Set();
    for (const num of nums) {
        if (seen.has(num)) {
            return num;
        }
        seen.add(num);
    }
};
