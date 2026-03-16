// Source: https://leetcode.com/problems/minimum-total-space-wasted-with-k-resizing-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are currently designing a dynamic array. You are given a 0-indexed integer array nums, where nums[i] is the number of elements that will be in the array at time i. In addition, you are given an integer k, the maximum number of times you can resize the array (to any size).
//
// The size of the array at time t, sizet, must be at least nums[t] because there needs to be enough space in the array to hold all the elements. The space wasted at time t is defined as sizet - nums[t], and the total space wasted is the sum of the space wasted across every time t where 0 <= t < nums.length.
//
// Return the minimum total space wasted if you can resize the array at most k times.
//
// Note: The array can have any size at the start and does not count towards the number of resizing operations.
//
// Example:
// Input: nums = [10,20], k = 0
// Output: 10
// Explanation: size = [20,20].
// We can set the initial size to be 20.
// The total wasted space is (20 - 10) + (20 - 20) = 10.
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 106
// 	0 <= k <= nums.length - 1
//

class Solution {
    public int minSpaceWastedKResizing(int[] nums, int k) {
        int n = nums.length;
        int[][] waste = new int[n][n];

        for (int i = 0; i < n; i++) {
            int max = nums[i];
            int sum = 0;
            for (int j = i; j < n; j++) {
                max = Math.max(max, nums[j]);
                sum += nums[j];
                waste[i][j] = max * (j - i + 1) - sum;
            }
        }

        int[][] dp = new int[n][k + 1];
        for (int i = 0; i < n; i++) {
            dp[i][0] = waste[0][i];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= k; j++) {
                dp[i][j] = Integer.MAX_VALUE;
                for (int p = 0; p < i; p++) {
                    dp[i][j] = Math.min(dp[i][j], dp[p][j - 1] + waste[p + 1][i]);
                }
            }
        }

        return dp[n - 1][k];            
    }
}
