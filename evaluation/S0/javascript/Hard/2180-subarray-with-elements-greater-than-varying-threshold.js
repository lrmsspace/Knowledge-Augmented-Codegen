// Source: https://leetcode.com/problems/subarray-with-elements-greater-than-varying-threshold/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer threshold.
//
// Find any subarray of nums of length k such that every element in the subarray is greater than threshold / k.
//
// Return the size of any such subarray. If there is no such subarray, return -1.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,3,4,3,1], threshold = 6
// Output: 3
// Explanation: The subarray [3,4,3] has a size of 3, and every element is greater than 6 / 3 = 2.
// Note that this is the only valid subarray.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i], threshold <= 109
//

/**
 * @param {number[]} nums
 * @param {number} threshold
 * @return {number}
 */
var validSubarraySize = function(nums, threshold) {
    const n = nums.length;          
    const stack = [];
    for (let i = 0; i < n; i++) {
        while (stack.length > 0 && nums[stack[stack.length - 1]] >= nums[i]) {
            const index = stack.pop();
            const size = stack.length === 0 ? i : i - stack[stack.length - 1] - 1;
            if (nums[index] > threshold / size) {
                return size;
            }
        }
        stack.push(i);
    }
    while (stack.length > 0) {
        const index = stack.pop();
        const size = stack.length === 0 ? n : n - stack[stack.length - 1] - 1;
        if (nums[index] > threshold / size) {
            return size;
        }
    }
    return -1; 
};
