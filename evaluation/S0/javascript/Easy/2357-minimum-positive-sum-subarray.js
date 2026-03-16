// Source: https://leetcode.com/problems/minimum-positive-sum-subarray/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums and two integers l and r. Your task is to find the minimum sum of a subarray whose size is between l and r (inclusive) and whose sum is greater than 0.
//
// Return the minimum sum of such a subarray. If no such subarray exists, return -1.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [3, -2, 1, 4], l = 2, r = 3
//
// Output: 1
//
// Explanation:
//
// The subarrays of length between l = 2 and r = 3 where the sum is greater than 0 are:
//
//
// 	[3, -2] with a sum of 1
// 	[1, 4] with a sum of 5
// 	[3, -2, 1] with a sum of 2
// 	[-2, 1, 4] with a sum of 3
//
//
// Out of these, the subarray [3, -2] has a sum of 1, which is the smallest positive sum. Hence, the answer is 1.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= l <= r <= nums.length
// 	-1000 <= nums[i] <= 1000
//

/**
 * @param {number[]} nums
 * @param {number} l
 * @param {number} r
 * @return {number}
 */
var minimumSumSubarray = function(nums, l, r) {
    let minPositiveSum = Infinity;
    const n = nums.length;
    for (let size = l; size <= r; size++) {
        for (let start = 0; start <= n - size; start++) {
            let sum = 0;
            for (let i = start; i < start + size; i++) {
                sum += nums[i];
            }
            if (sum > 0 && sum < minPositiveSum) {
                minPositiveSum = sum;
            }
        }
    }
    return minPositiveSum === Infinity ? -1 : minPositiveSum;
};