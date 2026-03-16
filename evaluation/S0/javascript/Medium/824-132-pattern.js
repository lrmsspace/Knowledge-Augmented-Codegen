// Source: https://leetcode.com/problems/132-pattern/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
//
// Return true if there is a 132 pattern in nums, otherwise, return false.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: false
// Explanation: There is no 132 pattern in the sequence.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 2 * 105
// 	-109 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var find132pattern = function(nums) {
    const n = nums.length;
    const stack = [];
    let third = -Infinity;

    for (let i = n - 1; i >= 0; i--) {
        if (nums[i] < third) {
            return true;
        }
        while (stack.length > 0 && nums[i] > stack[stack.length - 1]) {
            third = stack.pop();
        }
        stack.push(nums[i]);
    }

    return false;
};