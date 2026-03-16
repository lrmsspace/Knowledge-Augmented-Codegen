// Source: https://leetcode.com/problems/contains-duplicate-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums and an integer k, return true if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.
//
// Example:
// Input: nums = [1,2,3,1], k = 3
// Output: true
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	0 <= k <= 105
//

class Solution {
    public boolean containsNearbyDuplicate(int[] nums, int k) {
        Map<Integer, Integer> numIndices = new HashMap<>();

        for (int i = 0; i < nums.length; i++) {
            if (numIndices.containsKey(nums[i])) {
                int prevIndex = numIndices.get(nums[i]);
                if (i - prevIndex <= k) {
                    return true;
                }
            }
            numIndices.put(nums[i], i);
        }

        return false;           
    }
}
