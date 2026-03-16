// Source: https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr and an integer difference, return the length of the longest subsequence in arr which is an arithmetic sequence such that the difference between adjacent elements in the subsequence equals difference.
//
// A subsequence is a sequence that can be derived from arr by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: arr = [1,2,3,4], difference = 1
// Output: 4
// Explanation: The longest arithmetic subsequence is [1,2,3,4].
//
// Constraints:
// 1 <= arr.length <= 105
// 	-104 <= arr[i], difference <= 104
//

/**
 * @param {number[]} arr
 * @param {number} difference
 * @return {number}
 */
var longestSubsequence = function(arr, difference) {
    const dp = new Map();
    let maxLength = 0;
    for (const num of arr) {
        const prevNum = num - difference;
        const currLength = (dp.get(prevNum) || 0) + 1;
        dp.set(num, currLength);
        maxLength = Math.max(maxLength, currLength);
    }
    return maxLength;
        
};
