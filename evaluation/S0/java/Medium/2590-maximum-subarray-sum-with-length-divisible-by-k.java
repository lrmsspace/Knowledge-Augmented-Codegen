// Source: https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums and an integer k.
//
// Return the maximum sum of a subarray of nums, such that the size of the subarray is divisible by k.
//
// Example:
// Input: nums = [1,2], k = 1
//
// Output: 3
//
// Explanation:
//
// The subarray [1, 2] with sum 3 has length equal to 2 which is divisible by 1.
//
// Constraints:
// 1 <= k <= nums.length <= 2 * 105
// 	-109 <= nums[i] <= 109
//

class Solution {
    public long maxSubarraySum(int[] nums, int k) {
        long n = nums.length;
        long[] prefixSum = new long[(int)n + 1];
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        long maxSum = Long.MIN_VALUE;
        long[] minPrefixSum = new long[k];
        for (int i = 0; i < k; i++) {
            minPrefixSum[i] = Long.MAX_VALUE;
        }

        for (int i = 0; i <= n; i++) {
            int modIndex = i % k;
            if (minPrefixSum[modIndex] != Long.MAX_VALUE) {
                maxSum = Math.max(maxSum, prefixSum[i] - minPrefixSum[modIndex]);
            }
            minPrefixSum[modIndex] = Math.min(minPrefixSum[modIndex], prefixSum[i]);
        }

        return maxSum;          
    }
}
