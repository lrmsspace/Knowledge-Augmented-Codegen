// Source: https://leetcode.com/problems/maximum-sum-of-two-non-overlapping-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and two integers firstLen and secondLen, return the maximum sum of elements in two non-overlapping subarrays with lengths firstLen and secondLen.
//
// The array with length firstLen could occur before or after the array with length secondLen, but they have to be non-overlapping.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [0,6,5,2,2,5,1,9,4], firstLen = 1, secondLen = 2
// Output: 20
// Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.
//
// Constraints:
// 1 <= firstLen, secondLen <= 1000
// 	2 <= firstLen + secondLen <= 1000
// 	firstLen + secondLen <= nums.length <= 1000
// 	0 <= nums[i] <= 1000
//

/**
 * @param {number[]} nums
 * @param {number} firstLen
 * @param {number} secondLen
 * @return {number}
 */
var maxSumTwoNoOverlap = function(nums, firstLen, secondLen) {
    const n = nums.length;
    const prefixSum = new Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }
    let maxTotal = 0;
        
    const maxSum = (L, M) => {
        let maxL = 0;
        let maxTotal = 0;
        for (let i = L + M; i <= n; i++) {
            maxL = Math.max(maxL, prefixSum[i - M] - prefixSum[i - M - L]);
            const currentM = prefixSum[i] - prefixSum[i - M];
            maxTotal = Math.max(maxTotal, maxL + currentM);
        }
        return maxTotal;
    };
    maxTotal = Math.max(maxSum(firstLen, secondLen), maxSum(secondLen, firstLen));                                                      
    return maxTotal;        
};
