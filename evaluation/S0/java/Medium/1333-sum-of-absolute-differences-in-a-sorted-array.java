// Source: https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums sorted in non-decreasing order.
//
// Build and return an integer array result with the same length as nums such that result[i] is equal to the summation of absolute differences between nums[i] and all the other elements in the array.
//
// In other words, result[i] is equal to sum(|nums[i]-nums[j]|) where 0 <= j < nums.length and j != i (0-indexed).
//
// Example:
// Input: nums = [2,3,5]
// Output: [4,3,5]
// Explanation: Assuming the arrays are 0-indexed, then
// result[0] = |2-2| + |2-3| + |2-5| = 0 + 1 + 3 = 4,
// result[1] = |3-2| + |3-3| + |3-5| = 1 + 0 + 2 = 3,
// result[2] = |5-2| + |5-3| + |5-5| = 3 + 2 + 0 = 5.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= nums[i + 1] <= 104
//

class Solution {
    public int[] getSumAbsoluteDifferences(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];
        int[] prefixSum = new int[n];
        prefixSum[0] = nums[0];

        for (int i = 1; i < n; i++) {
            prefixSum[i] = prefixSum[i - 1] + nums[i];
        }

        for (int i = 0; i < n; i++) {
            int leftSum = i > 0 ? prefixSum[i - 1] : 0;
            int rightSum = prefixSum[n - 1] - prefixSum[i];

            int leftCount = i;
            int rightCount = n - i - 1;

            result[i] = (nums[i] * leftCount - leftSum) + (rightSum - nums[i] * rightCount);
        }

        return result;          
    }
}
