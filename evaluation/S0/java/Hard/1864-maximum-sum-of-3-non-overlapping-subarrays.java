// Source: https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, find three non-overlapping subarrays of length k with maximum sum and return them.
//
// Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.
//
// Example:
// Input: nums = [1,2,1,2,6,7,5,1], k = 2
// Output: [0,3,5]
// Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
// We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] < 216
// 	1 <= k <= floor(nums.length / 3)
//

class Solution {
    public int[] maxSumOfThreeSubarrays(int[] nums, int k) {
        int n = nums.length;
        int[] sum = new int[n - k + 1];
        int windowSum = 0;

        for (int i = 0; i < nums.length; i++) {
            windowSum += nums[i];
            if (i >= k) {
                windowSum -= nums[i - k];
            }
            if (i >= k - 1) {
                sum[i - k + 1] = windowSum;
            }
        }

        int[] left = new int[sum.length];
        int bestLeft = 0;
        for (int i = 0; i < sum.length; i++) {
            if (sum[i] > sum[bestLeft]) {
                bestLeft = i;
            }
            left[i] = bestLeft;
        }

        int[] right = new int[sum.length];
        int bestRight = sum.length - 1;
        for (int i = sum.length - 1; i >= 0; i--) {
            if (sum[i] >= sum[bestRight]) {
                bestRight = i;
            }
            right[i] = bestRight;
        }

        int maxTotal = 0;
        int[] result = new int[3];
        for (int j = k; j <= sum.length - k - 1; j++) {
            int i = left[j - k];
            int l = right[j + k];
            int total = sum[i] + sum[j] + sum[l];
            if (total > maxTotal) {
                maxTotal = total;
                result[0] = i;
                result[1] = j;
                result[2] = l;
            }
        }

        return result;          
    }
}
