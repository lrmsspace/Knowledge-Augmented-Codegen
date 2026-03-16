// Source: https://leetcode.com/problems/number-of-subarrays-with-and-value-of-k/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of integers nums and an integer k, return the number of subarrays of nums where the bitwise AND of the elements of the subarray equals k.
//
// Example:
// Input: nums = [1,1,1], k = 1
//
// Output: 6
//
// Explanation:
//
// All subarrays contain only 1's.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i], k <= 109
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var countSubarrays = function(nums, k) {
    let count = 0;
    for (let i = 0; i < nums.length; i++) {
        let andValue = nums[i];
        if (andValue === k) count++;
        for (let j = i + 1; j < nums.length; j++) {
            andValue &= nums[j];
            if (andValue === k) count++;
            if (andValue < k) break; // No need to continue if the AND value is already less than k
        }
    }
    return count;
};
