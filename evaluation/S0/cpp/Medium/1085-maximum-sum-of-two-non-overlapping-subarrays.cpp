// Source: https://leetcode.com/problems/maximum-sum-of-two-non-overlapping-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and two integers firstLen and secondLen, return the maximum sum of elements in two non-overlapping subarrays with lengths firstLen and secondLen.
//
// The array with length firstLen could occur before or after the array with length secondLen, but they have to be non-overlapping.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [0,6,5,2,2,5,1,9,4], firstLen = 1, secondLen = 2
// Output: 20
// Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.
//
// Constraints:
// 1 <= firstLen, secondLen <= 1000
// 	2 <= firstLen + secondLen <= 1000
// 	firstLen + secondLen <= nums.length <= 1000
// 	0 <= nums[i] <= 1000
//

class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size();
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        auto maxSum = [&](int len1, int len2) {
            int maxLen1 = 0;
            int result = 0;
            for (int i = len1 + len2; i <= n; ++i) {
                maxLen1 = max(maxLen1, prefixSum[i - len2] - prefixSum[i - len2 - len1]);
                result = max(result, maxLen1 + prefixSum[i] - prefixSum[i - len2]);
            }
            return result;
        };

        return max(maxSum(firstLen, secondLen), maxSum(secondLen, firstLen));           
    }
};
