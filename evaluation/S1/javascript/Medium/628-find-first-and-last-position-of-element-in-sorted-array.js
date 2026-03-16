// Source: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
//
// If target is not found in the array, return [-1, -1].
//
// You must write an algorithm with O(log n) runtime complexity.
//
// Example:
// Input: nums = [5,7,7,8,8,10], target = 8
// Output: [3,4]
//
// Constraints:
// 0 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	nums is a non-decreasing array.
// 	-109 <= target <= 109
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
 * @param {number} target
 * @return {number[]}
 */
var searchRange = function(nums, target) {
    const findBound = (isFirst) => {
        let low = 0;
        let high = nums.length - 1;
        let bound = -1;

        while (low <= high) {
            const mid = Math.floor((low + high) / 2);

            if (nums[mid] === target) {
                bound = mid;
                if (isFirst) {
                    high = mid - 1; // Move left to find the first occurrence
                } else {
                    low = mid + 1; // Move right to find the last occurrence
                }
            } else if (nums[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return bound;
    };

    const firstPos = findBound(true);
    if (firstPos === -1) {
        return [-1, -1]; // Target not found
    }
    const lastPos = findBound(false);

    return [firstPos, lastPos];
};
