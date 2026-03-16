// Source: https://leetcode.com/problems/contiguous-array/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
//
// Example:
// Input: nums = [0,1]
// Output: 2
// Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is either 0 or 1.
//

class Solution {
    public int findMaxLength(int[] nums) {
        Map<Integer, Integer> countIndexMap = new HashMap<>();
        countIndexMap.put(0, -1); // Initialize with count 0 at index -1
        int maxLength = 0;
        int count = 0;

        for (int i = 0; i < nums.length; i++) {
            // Increment count for 1, decrement for 0
            count += (nums[i] == 1) ? 1 : -1;

            if (countIndexMap.containsKey(count)) {
                // If the count has been seen before, calculate the length of the subarray
                int prevIndex = countIndexMap.get(count);
                maxLength = Math.max(maxLength, i - prevIndex);
            } else {
                // Store the first occurrence of this count
                countIndexMap.put(count, i);
            }
        }

        return maxLength;           
    }
}
