// Source: https://leetcode.com/problems/maximize-sum-of-array-after-k-negations/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums and an integer k, modify the array in the following way:
//
//
// 	choose an index i and replace nums[i] with -nums[i].
//
//
// You should apply this process exactly k times. You may choose the same index i multiple times.
//
// Return the largest possible sum of the array after modifying it in this way.
//
// Example:
// Input: nums = [4,2,3], k = 1
// Output: 5
// Explanation: Choose index 1 and nums becomes [4,-2,3].
//
// Constraints:
// 1 <= nums.length <= 104
// 	-100 <= nums[i] <= 100
// 	1 <= k <= 104
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var largestSumAfterKNegations = function(nums, k) {
    nums.sort((a, b) => a - b);
    for (let i = 0; i < nums.length && k > 0; i++) {
        if (nums[i] < 0) {
            nums[i] = -nums[i];
            k--;
        } else {
            break;
        }
    }
    if (k > 0 && k % 2 === 1) {
        nums.sort((a, b) => a - b);
        nums[0] = -nums[0];
    }
    return nums.reduce((sum, num) => sum + num, 0);
};
