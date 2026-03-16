// Source: https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a positive integer k.
// A subsequence sub of nums with length x is called valid if it satisfies:
//
//
// 	(sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.
//
// Return the length of the longest valid subsequence of nums.
//
// Example:
// Input: nums = [1,2,3,4,5], k = 2
//
// Output: 5
//
// Explanation:
//
// The longest valid subsequence is [1, 2, 3, 4, 5].
//
// Constraints:
// 2 <= nums.length <= 103
// 	1 <= nums[i] <= 107
// 	1 <= k <= 103
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maximumLength = function(nums, k) {
    let maxLength = 1;
    for (let i = 1; i < nums.length; i++) {
        if ((nums[i - 1] + nums[i]) % k === 0) {
            maxLength++;
        } else {
            maxLength = 1;
        }
    }
    return maxLength;
};
