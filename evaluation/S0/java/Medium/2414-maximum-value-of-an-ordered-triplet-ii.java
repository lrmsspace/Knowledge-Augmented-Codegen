// Source: https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums.
//
// Return the maximum value over all triplets of indices (i, j, k) such that i < j < k. If all such triplets have a negative value, return 0.
//
// The value of a triplet of indices (i, j, k) is equal to (nums[i] - nums[j]) * nums[k].
//
// Example:
// Input: nums = [12,6,1,2,7]
// Output: 77
// Explanation: The value of the triplet (0, 2, 4) is (nums[0] - nums[2]) * nums[4] = 77.
// It can be shown that there are no ordered triplets of indices with a value greater than 77.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//

class Solution {
    public long maximumTripletValue(int[] nums) {
        int n = nums.length;
        long maxTripletValue = 0;

        int[] leftMax = new int[n];
        leftMax[0] = nums[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = Math.max(leftMax[i - 1], nums[i]);
        }

        for (int j = 1; j < n - 1; j++) {
            long potentialValue = (long)(leftMax[j - 1] - nums[j]) * nums[j + 1];
            maxTripletValue = Math.max(maxTripletValue, potentialValue);
        }

        return maxTripletValue;         
    }
}
