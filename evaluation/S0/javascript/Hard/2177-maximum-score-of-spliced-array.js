// Source: https://leetcode.com/problems/maximum-score-of-spliced-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2, both of length n.
//
// You can choose two integers left and right where 0 <= left <= right < n and swap the subarray nums1[left...right] with the subarray nums2[left...right].
//
//
// 	For example, if nums1 = [1,2,3,4,5] and nums2 = [11,12,13,14,15] and you choose left = 1 and right = 2, nums1 becomes [1,12,13,4,5] and nums2 becomes [11,2,3,14,15].
//
//
// You may choose to apply the mentioned operation once or not do anything.
//
// The score of the arrays is the maximum of sum(nums1) and sum(nums2), where sum(arr) is the sum of all the elements in the array arr.
//
// Return the maximum possible score.
//
// A subarray is a contiguous sequence of elements within an array. arr[left...right] denotes the subarray that contains the elements of nums between indices left and right (inclusive).
//
// Example:
// Input: nums1 = [60,60,60], nums2 = [10,90,10]
// Output: 210
// Explanation: Choosing left = 1 and right = 1, we have nums1 = [60,90,60] and nums2 = [10,60,10].
// The score is max(sum(nums1), sum(nums2)) = max(210, 80) = 210.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 105
// 	1 <= nums1[i], nums2[i] <= 104
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var maximumsSplicedArray = function(nums1, nums2) {
    const n = nums1.length;
    const sum1 = nums1.reduce((a, b) => a + b, 0);
    const sum2 = nums2.reduce((a, b) => a + b, 0);
    let maxDiff1 = 0;
    let maxDiff2 = 0;
    let currentDiff1 = 0;
    let currentDiff2 = 0;
    for (let i = 0; i < n; i++) {
        currentDiff1 = Math.max(0, currentDiff1 + nums2[i] - nums1[i]);
        maxDiff1 = Math.max(maxDiff1, currentDiff1);
        currentDiff2 = Math.max(0, currentDiff2 + nums1[i] - nums2[i]);
        maxDiff2 = Math.max(maxDiff2, currentDiff2);
    }
    return Math.max(sum1 + maxDiff1, sum2 + maxDiff2);
};
