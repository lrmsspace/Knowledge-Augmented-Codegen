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
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        const int MOD = 1e9 + 7;
        long long maxSubArraySum = 0, currentSum = 0;
        long long totalSum = 0;
        long long maxPrefixSum = 0, currentPrefixSum = 0;
        long long maxSuffixSum = 0, currentSuffixSum = 0;

        // Calculate max sub-array sum using Kadane's algorithm
        for (int num : arr) {
            currentSum = max(0LL, currentSum + num);
            maxSubArraySum = max(maxSubArraySum, currentSum);
            totalSum += num;
        }

        // Calculate max prefix sum
        for (int num : arr) {
            currentPrefixSum += num;
            maxPrefixSum = max(maxPrefixSum, currentPrefixSum);
        }

        // Calculate max suffix sum
        for (int i = arr.size() - 1; i >= 0; --i) {
            currentSuffixSum += arr[i];
            maxSuffixSum = max(maxSuffixSum, currentSuffixSum);
        }

        if (k == 1) {
            return maxSubArraySum % MOD;
        } else {
            long long result = max({maxSubArraySum, maxPrefixSum + maxSuffixSum, 
                                   maxPrefixSum + max(0LL, totalSum) * (k - 2) + maxSuffixSum});
            return result % MOD;
        }           
    }
};
