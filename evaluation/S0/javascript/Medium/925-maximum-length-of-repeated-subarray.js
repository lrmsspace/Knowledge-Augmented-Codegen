// Source: https://leetcode.com/problems/maximum-length-of-repeated-subarray/   |   Difficulty: Medium
//
// Problem Description:
// Given two integer arrays nums1 and nums2, return the maximum length of a subarray that appears in both arrays.
//
// Example:
// Input: nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
// Output: 3
// Explanation: The repeated subarray with maximum length is [3,2,1].
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 1000
// 	0 <= nums1[i], nums2[i] <= 100
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var findLength = function(nums1, nums2) {
    const m = nums1.length;
    const n = nums2.length;
    const dp = Array.from({ length: m + 1 }, () => new Array(n + 1).fill(0));
    let maxLength = 0;
    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            if (nums1[i - 1] === nums2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                maxLength = Math.max(maxLength, dp[i][j]);
            }
        }
    }
    return maxLength;
};