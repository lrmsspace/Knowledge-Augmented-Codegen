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
    public int subarraySum(int[] nums, int k) {
        int count = 0;
        int sum = 0;
        Map<Integer, Integer> prefixSumCount = new HashMap<>();
        prefixSumCount.put(0, 1); // Base case: one way to have a sum of 0

        for (int num : nums) {
            sum += num;

            // Check if there is a prefix sum that when subtracted from current sum equals k
            if (prefixSumCount.containsKey(sum - k)) {
                count += prefixSumCount.get(sum - k);
            }

            // Update the count of the current prefix sum
            prefixSumCount.put(sum, prefixSumCount.getOrDefault(sum, 0) + 1);
        }

        return count;           
    }
}
