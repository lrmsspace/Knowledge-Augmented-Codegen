// Source: https://leetcode.com/problems/reverse-subarray-to-maximize-array-value/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. The value of this array is defined as the sum of |nums[i] - nums[i + 1]| for all 0 <= i < nums.length - 1.
//
// You are allowed to select any subarray of the given array and reverse it. You can perform this operation only once.
//
// Find maximum possible value of the final array.
//
// Example:
// Input: nums = [2,3,1,5,4]
// Output: 10
// Explanation: By reversing the subarray [3,1,5] the array becomes [2,5,1,3,4] whose value is 10.
//
// Constraints:
// 2 <= nums.length <= 3 * 104
// 	-105 <= nums[i] <= 105
// 	The answer is guaranteed to fit in a 32-bit integer.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxValueAfterReverse = function(nums) {
    const n = nums.length;
    let originalValue = 0;
    for (let i = 0; i < n - 1; i++) {
        originalValue += Math.abs(nums[i] - nums[i + 1]);
    }
    let maxGain = 0;
    for (let i = 0; i < n - 1; i++) {
        maxGain = Math.max(maxGain, Math.abs(nums[0] - nums[i + 1]) - Math.abs(nums[i] - nums[i + 1]));
        maxGain = Math.max(maxGain, Math.abs(nums[n - 1] - nums[i]) - Math.abs(nums[i] - nums[i + 1]));
    }
    for (let i = 1; i < n - 1; i++) {
        maxGain = Math.max(maxGain, Math.abs(nums[i - 1] - nums[i + 1]) - Math.abs(nums[i - 1] - nums[i]) - Math.abs(nums[i] - nums[i + 1]));
    }
    return originalValue + maxGain; 
};
