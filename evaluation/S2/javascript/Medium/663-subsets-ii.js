// Source: https://leetcode.com/problems/subsets-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
//
// The solution set must not contain duplicate subsets. Return the solution in any order.
//
// Example:
// Input: nums = [1,2,2]
// Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
//
// Constraints:
// 1 <= nums.length <= 10
// 	-10 <= nums[i] <= 10
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
 * @return {number[][]}
 */
var subsetsWithDup = function(nums) {
    const res = [];
    nums.sort((a, b) => a - b);
    backtrack(nums, 0, [], res);
    return res;
};

function backtrack(nums, start, path, res) {
    res.push([...path]);
    for (let i = start; i < nums.length; i++) {
        if (i > start && nums[i] === nums[i - 1]) continue;
        path.push(nums[i]);
        backtrack(nums, i + 1, path, res);
        path.pop();
    }
}