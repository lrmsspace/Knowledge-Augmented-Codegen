// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums and an integer target, return the maximum number of non-empty non-overlapping subarrays such that the sum of values in each subarray is equal to target.
//
// Example:
// Input: nums = [1,1,1,1,1], target = 2
// Output: 2
// Explanation: There are 2 non-overlapping subarrays [1,1,1,1,1] with sum equals to target(2).
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
// 	0 <= target <= 106
//

class Solution {
    public int maxNonOverlapping(int[] nums, int target) {
        Set<Integer> seenSums = new HashSet<>();
        seenSums.add(0);
        int count = 0;
        int currentSum = 0;

        for (int num : nums) {
            currentSum += num;

            if (seenSums.contains(currentSum - target)) {
                count++;
                currentSum = 0;
                seenSums.clear();
                seenSums.add(0);
            } else {
                seenSums.add(currentSum);
            }
        }

        return count;           
    }
}
