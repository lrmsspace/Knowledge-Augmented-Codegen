// Source: https://leetcode.com/problems/subarray-sum-equals-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,1,1], k = 2
// Output: 2
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	-1000 <= nums[i] <= 1000
// 	-107 <= k <= 107
//

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixSumCount;
        prefixSumCount[0] = 1;  // Base case: one way to have a prefix sum of 0
        int currentSum = 0;
        int result = 0;

        for (int num : nums) {
            currentSum += num;

            // Check if there is a prefix sum that when subtracted from currentSum gives k
            if (prefixSumCount.find(currentSum - k) != prefixSumCount.end()) {
                result += prefixSumCount[currentSum - k];
            }

            // Record the current prefix sum
            prefixSumCount[currentSum]++;
        }

        return result;          
    }
};
