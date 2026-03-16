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

class Solution {
    public int kConcatenationMaxSum(int[] arr, int k) {
        long mod = 1_000_000_007;
        long maxSum = 0, currentSum = 0, totalSum = 0;

        for (int num : arr) {
            totalSum += num;
            currentSum = Math.max(num, currentSum + num);
            maxSum = Math.max(maxSum, currentSum);
        }

        if (k == 1) {
            return (int) (maxSum % mod);
        }

        long maxPrefixSum = 0, prefixSum = 0;
        for (int num : arr) {
            prefixSum += num;
            maxPrefixSum = Math.max(maxPrefixSum, prefixSum);
        }

        long maxSuffixSum = 0, suffixSum = 0;
        for (int i = arr.length - 1; i >= 0; i--) {
            suffixSum += arr[i];
            maxSuffixSum = Math.max(maxSuffixSum, suffixSum);
        }

        if (totalSum > 0) {
            maxSum = Math.max(maxSum, maxPrefixSum + maxSuffixSum + (k - 2) * totalSum);
        } else {
            maxSum = Math.max(maxSum, maxPrefixSum + maxSuffixSum);
        }

        return (int) (maxSum % mod);            
    }
}
