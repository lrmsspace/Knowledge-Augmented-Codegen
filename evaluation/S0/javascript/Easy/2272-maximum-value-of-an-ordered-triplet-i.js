// Source: https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums.
//
// Return the maximum value over all triplets of indices (i, j, k) such that i < j < k. If all such triplets have a negative value, return 0.
//
// The value of a triplet of indices (i, j, k) is equal to (nums[i] - nums[j]) * nums[k].
//
// Example:
// Input: nums = [12,6,1,2,7]
// Output: 77
// Explanation: The value of the triplet (0, 2, 4) is (nums[0] - nums[2]) * nums[4] = 77.
// It can be shown that there are no ordered triplets of indices with a value greater than 77.
//
// Constraints:
// 3 <= nums.length <= 100
// 	1 <= nums[i] <= 106
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maximumTripletValue = function(nums) {
    let maxValue = 0;
    const n = nums.length;
    for (let i = 0; i < n - 2; i++) {
        for (let j = i + 1; j < n - 1; j++) {
            for (let k = j + 1; k < n; k++) {
                const value = (nums[i] - nums[j]) * nums[k];
                if (value > maxValue) {
                    maxValue = value;
                }
            }
        }
    }
    return maxValue;
};