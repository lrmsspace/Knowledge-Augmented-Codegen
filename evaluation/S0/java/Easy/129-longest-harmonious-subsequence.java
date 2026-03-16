// Source: https://leetcode.com/problems/longest-harmonious-subsequence/   |   Difficulty: Easy
//
// Problem Description:
// We define a harmonious array as an array where the difference between its maximum value and its minimum value is exactly 1.
//
// Given an integer array nums, return the length of its longest harmonious subsequence among all its possible subsequences.
//
// Example:
// Input: nums = [1,3,2,2,5,2,3,7]
//
// Output: 5
//
// Explanation:
//
// The longest harmonious subsequence is [3,2,2,2,3].
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	-109 <= nums[i] <= 109
//

class Solution {
    public int findLHS(int[] nums) {
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        int longestLength = 0;

        // Count the frequency of each number in the array
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }

        // Check for each unique number if its consecutive number exists
        for (int key : frequencyMap.keySet()) {
            if (frequencyMap.containsKey(key + 1)) {
                int currentLength = frequencyMap.get(key) + frequencyMap.get(key + 1);
                longestLength = Math.max(longestLength, currentLength);
            }
        }

        return longestLength;           
    }
}
