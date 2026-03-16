// Source: https://leetcode.com/problems/k-concatenation-maximum-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr and an integer k, modify the array by repeating it k times.
//
// For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].
//
// Return the maximum sub-array sum in the modified array. Note that the length of the sub-array can be 0 and its sum in that case is 0.
//
// As the answer can be very large, return the answer modulo 109 + 7.
//
// Example:
// Input: arr = [1,2], k = 3
// Output: 9
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= k <= 105
// 	-104 <= arr[i] <= 104
//

/**
 * @param {number[]} arr
 * @param {number} k
 * @return {number}
 */
var kConcatenationMaxSum = function(arr, k) {
    const MOD = 1e9 + 7;
    const n = arr.length;
    let maxSubArraySum = 0;
    let currentSum = 0;
    let totalSum = 0;
    let maxPrefixSum = 0;
    let prefixSum = 0;
    let maxSuffixSum = 0;
    let suffixSum = 0;
    // Calculate total sum, max sub-array sum, max prefix sum, and max suffix sum
    for (let i = 0; i < n; i++) {
        totalSum += arr[i];
        currentSum += arr[i];
        if (currentSum < 0) currentSum = 0;
        maxSubArraySum = Math.max(maxSubArraySum, currentSum);
        prefixSum += arr[i];
        maxPrefixSum = Math.max(maxPrefixSum, prefixSum);
    }
    suffixSum = 0;
    for (let i = n - 1; i >= 0; i--) {
        suffixSum += arr[i];
        maxSuffixSum = Math.max(maxSuffixSum, suffixSum);
    }
    if (k === 1) {
        return maxSubArraySum % MOD;
    } else {
        if (totalSum > 0) {
            return (maxSuffixSum + maxPrefixSum + (k - 2) * totalSum) % MOD;
        } else {
            return Math.max(maxSubArraySum, maxSuffixSum + maxPrefixSum) % MOD;
        }
    }
        
            
};
