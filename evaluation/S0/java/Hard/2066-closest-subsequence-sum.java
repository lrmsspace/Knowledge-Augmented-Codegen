// Source: https://leetcode.com/problems/closest-subsequence-sum/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer goal.
//
// You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal. That is, if the sum of the subsequence's elements is sum, then you want to minimize the absolute difference abs(sum - goal).
//
// Return the minimum possible value of abs(sum - goal).
//
// Note that a subsequence of an array is an array formed by removing some elements (possibly all or none) of the original array.
//
// Example:
// Input: nums = [5,-7,3,5], goal = 6
// Output: 0
// Explanation: Choose the whole array as a subsequence, with a sum of 6.
// This is equal to the goal, so the absolute difference is 0.
//
// Constraints:
// 1 <= nums.length <= 40
// 	-107 <= nums[i] <= 107
// 	-109 <= goal <= 109
//

class Solution {
    public int minAbsDifference(int[] nums, int goal) {
        int n = nums.length;
        List<Integer> leftSums = new ArrayList<>();
        List<Integer> rightSums = new ArrayList<>();

        // Generate all possible sums for the left half
        generateSums(nums, 0, n / 2, 0, leftSums);
        // Generate all possible sums for the right half
        generateSums(nums, n / 2, n, 0, rightSums);

        Collections.sort(rightSums);
        int minDiff = Integer.MAX_VALUE;

        // For each sum in the left half, find the closest sum in the right half
        for (int leftSum : leftSums) {
            int target = goal - leftSum;
            int idx = Collections.binarySearch(rightSums, target);
            if (idx < 0) {
                idx = -(idx + 1);
            }

            // Check the closest sums found
            if (idx < rightSums.size()) {
                minDiff = Math.min(minDiff, Math.abs(leftSum + rightSums.get(idx) - goal));
            }
            if (idx > 0) {
                minDiff = Math.min(minDiff, Math.abs(leftSum + rightSums.get(idx - 1) - goal));
            }
        }

        return minDiff;         
    }
}
