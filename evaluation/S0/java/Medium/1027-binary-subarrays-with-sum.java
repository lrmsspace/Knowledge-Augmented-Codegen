// Source: https://leetcode.com/problems/binary-subarrays-with-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary array nums and an integer goal, return the number of non-empty subarrays with a sum goal.
//
// A subarray is a contiguous part of the array.
//
// Example:
// Input: nums = [1,0,1,0,1], goal = 2
// Output: 4
// Explanation: The 4 subarrays are bolded and underlined below:
// [1,0,1,0,1]
// [1,0,1,0,1]
// [1,0,1,0,1]
// [1,0,1,0,1]
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	nums[i] is either 0 or 1.
// 	0 <= goal <= nums.length
//

class Solution {
    public int numSubarraysWithSum(int[] nums, int goal) {
        int n = nums.length;
        int[] prefixSumCount = new int[n + 1];
        prefixSumCount[0] = 1; // There's one way to have a prefix sum of 0 (by taking no elements)

        int currentPrefixSum = 0;
        int result = 0;

        for (int num : nums) {
            currentPrefixSum += num;

            // Check if there is a prefix sum that, when subtracted from the current prefix sum, equals the goal
            if (currentPrefixSum - goal >= 0) {
                result += prefixSumCount[currentPrefixSum - goal];
            }

            // Increment the count of the current prefix sum
            prefixSumCount[currentPrefixSum]++;
        }

        return result;          
    }
}
