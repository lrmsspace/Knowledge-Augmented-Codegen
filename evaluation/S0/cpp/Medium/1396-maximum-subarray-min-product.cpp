// Source: https://leetcode.com/problems/maximum-subarray-min-product/   |   Difficulty: Medium
//
// Problem Description:
// The min-product of an array is equal to the minimum value in the array multiplied by the array's sum.
//
//
// 	For example, the array [3,2,5] (minimum value is 2) has a min-product of 2 * (3+2+5) = 2 * 10 = 20.
//
//
// Given an array of integers nums, return the maximum min-product of any non-empty subarray of nums. Since the answer may be large, return it modulo 109 + 7.
//
// Note that the min-product should be maximized before performing the modulo operation. Testcases are generated such that the maximum min-product without modulo will fit in a 64-bit signed integer.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [1,2,3,2]
// Output: 14
// Explanation: The maximum min-product is achieved with the subarray [2,3,2] (minimum value is 2).
// 2 * (2+3+2) = 2 * 7 = 14.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 107
//

class Solution {
public:
    int maxSumMinProduct(vector<int>& nums) {
        int n = nums.size();
        vector<long long> prefixSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        stack<int> monoStack;
        long long maxMinProduct = 0;
        for (int i = 0; i <= n; ++i) {
            while (!monoStack.empty() && (i == n || nums[monoStack.top()] >= nums[i])) {
                int minIndex = monoStack.top();
                monoStack.pop();
                int leftIndex = monoStack.empty() ? -1 : monoStack.top();
                long long subarraySum = prefixSum[i] - prefixSum[leftIndex + 1];
                long long minProduct = subarraySum * nums[minIndex];
                maxMinProduct = max(maxMinProduct, minProduct);
            }
            monoStack.push(i);
        }

        return maxMinProduct % 1000000007;          
    }
};
