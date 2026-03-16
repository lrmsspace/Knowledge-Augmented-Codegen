// Source: https://leetcode.com/problems/get-maximum-in-generated-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer n. A 0-indexed integer array nums of length n + 1 is generated in the following way:
//
//
// 	nums[0] = 0
// 	nums[1] = 1
// 	nums[2 * i] = nums[i] when 2 <= 2 * i <= n
// 	nums[2 * i + 1] = nums[i] + nums[i + 1] when 2 <= 2 * i + 1 <= n
//
//
// Return the maximum integer in the array nums​​​.
//
// Example:
// Input: n = 7
// Output: 3
// Explanation: According to the given rules:
//   nums[0] = 0
//   nums[1] = 1
//   nums[(1 * 2) = 2] = nums[1] = 1
//   nums[(1 * 2) + 1 = 3] = nums[1] + nums[2] = 1 + 1 = 2
//   nums[(2 * 2) = 4] = nums[2] = 1
//   nums[(2 * 2) + 1 = 5] = nums[2] + nums[3] = 1 + 2 = 3
//   nums[(3 * 2) = 6] = nums[3] = 2
//   nums[(3 * 2) + 1 = 7] = nums[3] + nums[4] = 2 + 1 = 3
// Hence, nums = [0,1,1,2,1,3,2,3], and the maximum is max(0,1,1,2,1,3,2,3) = 3.
//
// Constraints:
// 0 <= n <= 100
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
 * @return {number}
 */
var getMaximumGenerated = function(n) {
    if (n === 0) return 0;
    const nums = new Array(n + 1).fill(0);
    nums[1] = 1;
    let max = 1;
    for (let i = 2; i <= n; i++) {
        if (i % 2 === 0) {
            nums[i] = nums[i / 2];
        } else {
            nums[i] = nums[(i - 1) / 2] + nums[(i - 1) / 2 + 1];
        }
        max = Math.max(max, nums[i]);
    }
    return max;
};
