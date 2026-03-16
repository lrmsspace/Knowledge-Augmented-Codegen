// Source: https://leetcode.com/problems/number-of-longest-increasing-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the number of longest increasing subsequences.
//
// Notice that the sequence has to be strictly increasing.
//
// Example:
// Input: nums = [1,3,5,4,7]
// Output: 2
// Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].
//
// Constraints:
// 1 <= nums.length <= 2000
// 	-106 <= nums[i] <= 106
// 	The answer is guaranteed to fit inside a 32-bit integer.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var findNumberOfLIS = function(nums) {
    const n = nums.length;
    if (n === 0) return 0;
    const lengths = new Array(n).fill(1);
    const counts = new Array(n).fill(1);
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                if (lengths[j] + 1 > lengths[i]) {
                    lengths[i] = lengths[j] + 1;
                    counts[i] = counts[j];
                } else if (lengths[j] + 1 === lengths[i]) {
                    counts[i] += counts[j];
                }
            }
        }
    }
    const maxLength = Math.max(...lengths);
    let result = 0;
    for (let i = 0; i < n; i++) {
        if (lengths[i] === maxLength) {
            result += counts[i];
        }
    }
    return result;
};