// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. In one operation, you can replace any element in nums with any integer.
//
// nums is considered continuous if both of the following conditions are fulfilled:
//
//
// 	All elements in nums are unique.
// 	The difference between the maximum element and the minimum element in nums equals nums.length - 1.
//
//
// For example, nums = [4, 2, 5, 3] is continuous, but nums = [1, 2, 3, 5, 6] is not continuous.
//
// Return the minimum number of operations to make nums continuous.
//
// Example:
// Input: nums = [4,2,5,3]
// Output: 0
// Explanation: nums is already continuous.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minOperations = function(nums) {
    const n = nums.length;
    const uniqueNums = Array.from(new Set(nums)).sort((a, b) => a - b);
    let left = 0;
    let maxLength = 1;
    for (let right = 0; right < uniqueNums.length; right += 1) {
        while (uniqueNums[right] - uniqueNums[left] > n - 1) {
            left += 1;
        }
        maxLength = Math.max(maxLength, right - left + 1);
    }
    return n - maxLength;   
};
