// Source: https://leetcode.com/problems/count-subarrays-with-fixed-bounds/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers minK and maxK.
//
// A fixed-bound subarray of nums is a subarray that satisfies the following conditions:
//
//
// 	The minimum value in the subarray is equal to minK.
// 	The maximum value in the subarray is equal to maxK.
//
//
// Return the number of fixed-bound subarrays.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
// Output: 2
// Explanation: The fixed-bound subarrays are [1,3,5] and [1,3,5,2].
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i], minK, maxK <= 106
//

/**
 * @param {number[]} nums
 * @param {number} minK
 * @param {number} maxK
 * @return {number}
 */
var countSubarrays = function(nums, minK, maxK) {
    let count = 0;
    let lastMinK = -1;
    let lastMaxK = -1;
    let lastInvalid = -1;
    for (let i = 0; i < nums.length; i++) {
        if (nums[i] < minK || nums[i] > maxK) {
            lastInvalid = i;
        }
        if (nums[i] === minK) {
            lastMinK = i;
        }
        if (nums[i] === maxK) {
            lastMaxK = i;
        }
        count += Math.max(0, Math.min(lastMinK, lastMaxK) - lastInvalid);
    }
    return count;
};
