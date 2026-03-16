// Source: https://leetcode.com/problems/subarray-sums-divisible-by-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [4,5,0,-2,-3,1], k = 5
// Output: 7
// Explanation: There are 7 subarrays with a sum divisible by k = 5:
// [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	-104 <= nums[i] <= 104
// 	2 <= k <= 104
//

class Solution {
    public int subarraysDivByK(int[] nums, int k) {
        int count = 0;
        int prefixSum = 0;
        Map<Integer, Integer> modCountMap = new HashMap<>();
        modCountMap.put(0, 1); // Initialize with mod 0 having one occurrence

        for (int num : nums) {
            prefixSum += num;
            int mod = ((prefixSum % k) + k) % k; // Handle negative mods

            if (modCountMap.containsKey(mod)) {
                count += modCountMap.get(mod);
            }

            modCountMap.put(mod, modCountMap.getOrDefault(mod, 0) + 1);
        }

        return count;           
    }
}
