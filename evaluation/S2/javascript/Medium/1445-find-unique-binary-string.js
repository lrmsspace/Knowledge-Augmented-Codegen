// Source: https://leetcode.com/problems/find-unique-binary-string/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings nums containing n unique binary strings each of length n, return a binary string of length n that does not appear in nums. If there are multiple answers, you may return any of them.
//
// Example:
// Input: nums = ["01","10"]
// Output: "11"
// Explanation: "11" does not appear in nums. "00" would also be correct.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 16
// 	nums[i].length == n
// 	nums[i] is either '0' or '1'.
// 	All the strings of nums are unique.
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
 * @param {string[]} nums
 * @return {string}
 */
var findDifferentBinaryString = function(nums) {
    const n = nums.length;
    const numSet = new Set(nums);
    for (let i = 0; i < (1 << n); i++) {
        const binaryStr = i.toString(2).padStart(n, '0');
        if (!numSet.has(binaryStr)) {
            return binaryStr;
        }
    }
};
