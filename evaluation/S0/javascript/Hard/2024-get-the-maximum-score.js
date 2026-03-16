// Source: https://leetcode.com/problems/get-the-maximum-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given two sorted arrays of distinct integers nums1 and nums2.
//
// A valid path is defined as follows:
//
//
// 	Choose array nums1 or nums2 to traverse (from index-0).
// 	Traverse the current array from left to right.
// 	If you are reading any value that is present in nums1 and nums2 you are allowed to change your path to the other array. (Only one repeated value is considered in the valid path).
//
//
// The score is defined as the sum of unique values in a valid path.
//
// Return the maximum score you can obtain of all possible valid paths. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums1 = [2,4,5,8,10], nums2 = [4,6,8,9]
// Output: 30
// Explanation: Valid paths:
// [2,4,5,8,10], [2,4,5,8,9], [2,4,6,8,9], [2,4,6,8,10],  (starting from nums1)
// [4,6,8,9], [4,5,8,10], [4,5,8,9], [4,6,8,10]    (starting from nums2)
// The maximum is obtained with the path in green [2,4,6,8,10].
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 105
// 	1 <= nums1[i], nums2[i] <= 107
// 	nums1 and nums2 are strictly increasing.
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var maxSum = function(nums1, nums2) {
    const MOD = 1e9 + 7;
    let i = 0;
    let j = 0;
    let sum1 = 0;
    let sum2 = 0;
    let result = 0;
    const MOD = 1e9 + 7;
    while (i < nums1.length && j < nums2.length) {
        if (nums1[i] < nums2[j]) {
            sum1 += nums1[i++];
        } else if (nums1[i] > nums2[j]) {
            sum2 += nums2[j++];
        } else {
            result += Math.max(sum1, sum2) + nums1[i];
            result %= MOD;
            i++;
            j++;
            sum1 = 0;
            sum2 = 0;
        }
    }
    while (i < nums1.length) {
        sum1 += nums1[i++];
    }
    while (j < nums2.length) {
        sum2 += nums2[j++];
    }
    result += Math.max(sum1, sum2);
    return result % MOD;
};
