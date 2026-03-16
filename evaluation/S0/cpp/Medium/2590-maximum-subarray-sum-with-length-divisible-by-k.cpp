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
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> prefixSums(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSums[i + 1] = prefixSums[i] + nums[i];
        }

        long long maxSum = LLONG_MIN;
        vector<long long> minPrefixSums(k, LLONG_MAX);
        for (int i = 0; i <= n; ++i) {
            int modIndex = i % k;
            if (minPrefixSums[modIndex] != LLONG_MAX) {
                maxSum = max(maxSum, prefixSums[i] - minPrefixSums[modIndex]);
            }
            minPrefixSums[modIndex] = min(minPrefixSums[modIndex], prefixSums[i]);
        }

        return maxSum;          
    }
};
