// Source: https://leetcode.com/problems/the-number-of-beautiful-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of positive integers and a positive integer k.
//
// A subset of nums is beautiful if it does not contain two integers with an absolute difference equal to k.
//
// Return the number of non-empty beautiful subsets of the array nums.
//
// A subset of nums is an array that can be obtained by deleting some (possibly none) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [2,4,6], k = 2
// Output: 4
// Explanation: The beautiful subsets of the array nums are: [2], [4], [6], [2, 6].
// It can be proved that there are only 4 beautiful subsets in the array [2,4,6].
//
// Constraints:
// 1 <= nums.length <= 18
// 	1 <= nums[i], k <= 1000
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
 * @param {number} k
 * @return {number}
 */
var beautifulSubsets = function(nums, k) {
     const backtrack = (index, currentSubset) => {
        if (index === nums.length) {
            return currentSubset.length > 0 ? 1 : 0;
        }
        // Exclude the current number
        let count = backtrack(index + 1, currentSubset);
        // Include the current number if it doesn't violate the condition
        if (!currentSubset.some(num => Math.abs(num - nums[index]) === k)) {
            currentSubset.push(nums[index]);
            count += backtrack(index + 1, currentSubset);
            currentSubset.pop();
        }
        return count;
    };
    return backtrack(0, []);
};
