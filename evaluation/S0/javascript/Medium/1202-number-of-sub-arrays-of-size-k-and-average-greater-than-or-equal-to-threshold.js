// Source: https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr and two integers k and threshold, return the number of sub-arrays of size k and average greater than or equal to threshold.
//
// Example:
// Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
// Output: 3
// Explanation: Sub-arrays [2,5,5],[5,5,5] and [5,5,8] have averages 4, 5 and 6 respectively. All other sub-arrays of size 3 have averages less than 4 (the threshold).
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i] <= 104
// 	1 <= k <= arr.length
// 	0 <= threshold <= 104
//

/**
 * @param {number[]} arr
 * @param {number} k
 * @param {number} threshold
 * @return {number}
 */
var numOfSubarrays = function(arr, k, threshold) {
    let count = 0;
    const requiredSum = threshold * k;
    let windowSum = 0;
    for (let i = 0; i < arr.length; i++) {
        windowSum += arr[i];
        if (i >= k - 1) {
            if (windowSum >= requiredSum) {
                count++;
            }
            windowSum -= arr[i - k + 1];
        }
    }
    return count;
        
};
