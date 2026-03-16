// Source: https://leetcode.com/problems/detect-pattern-of-length-m-repeated-k-or-more-times/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of positive integers arr, find a pattern of length m that is repeated k or more times.
//
// A pattern is a subarray (consecutive sub-sequence) that consists of one or more values, repeated multiple times consecutively without overlapping. A pattern is defined by its length and the number of repetitions.
//
// Return true if there exists a pattern of length m that is repeated k or more times, otherwise return false.
//
// Example:
// Input: arr = [1,2,4,4,4,4], m = 1, k = 3
// Output: true
// Explanation: The pattern (4) of length 1 is repeated 4 consecutive times. Notice that pattern can be repeated k or more times but not less.
//
// Constraints:
// 2 <= arr.length <= 100
// 	1 <= arr[i] <= 100
// 	1 <= m <= 100
// 	2 <= k <= 100
//

/**
 * @param {number[]} arr
 * @param {number} m
 * @param {number} k
 * @return {boolean}
 */
var containsPattern = function(arr, m, k) {
    const n = arr.length;
    for (let i = 0; i <= n - m * k; i++) {
        let match = true;
        for (let j = 0; j < m; j++) {
            for (let l = 1; l < k; l++) {
                if (arr[i + j] !== arr[i + j + l * m]) {
                    match = false;
                    break;
                }
            }
            if (!match) {
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
};