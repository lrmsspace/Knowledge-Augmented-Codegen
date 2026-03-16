// Source: https://leetcode.com/problems/find-the-maximum-length-of-a-good-subsequence-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a non-negative integer k. A sequence of integers seq is called good if there are at most k indices i in the range [0, seq.length - 2] such that seq[i] != seq[i + 1].
//
// Return the maximum possible length of a good subsequence of nums.
//
// Example:
// Input: nums = [1,2,1,1,3], k = 2
//
// Output: 4
//
// Explanation:
//
// The maximum length subsequence is [1,2,1,1,3].
//
// Constraints:
// 1 <= nums.length <= 5 * 103
// 	1 <= nums[i] <= 109
// 	0 <= k <= min(50, nums.length)
//

class Solution {
    public int maximumLength(int[] nums, int k) {
        int n = nums.length;
        int[][] dp = new int[n + 1][k + 2];

        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = dp[i + 1][j] + 1;

                if (j < k) {
                    for (int l = i + 1; l < n; l++) {
                        if (nums[l] != nums[i]) {
                            dp[i][j] = Math.max(dp[i][j], dp[l][j + 1] + 1);
                        }
                    }
                }
            }
        }

        return dp[0][0];            
    }
}
