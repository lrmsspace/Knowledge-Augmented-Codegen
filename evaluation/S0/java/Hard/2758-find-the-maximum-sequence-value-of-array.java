// Source: https://leetcode.com/problems/find-the-maximum-sequence-value-of-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k.
//
// The value of a sequence seq of size 2 * x is defined as:
//
//
// 	(seq[0] OR seq[1] OR ... OR seq[x - 1]) XOR (seq[x] OR seq[x + 1] OR ... OR seq[2 * x - 1]).
//
//
// Return the maximum value of any subsequence of nums having size 2 * k.
//
// Example:
// Input: nums = [2,6,7], k = 1
//
// Output: 5
//
// Explanation:
//
// The subsequence [2, 7] has the maximum value of 2 XOR 7 = 5.
//
// Constraints:
// 2 <= nums.length <= 400
// 	1 <= nums[i] < 27
// 	1 <= k <= nums.length / 2
//

class Solution {
    public int maxValue(int[] nums, int k) {
        int n = nums.length;
        int[][][] dp = new int[n + 1][k + 1][1 << 5];

        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j <= k; j++) {
                for (int b = 0; b < (1 << 5); b++) {
                    dp[i][j][b] = dp[i + 1][j][b];
                    if (j > 0) {
                        dp[i][j][b] = Math.max(dp[i][j][b],
                                dp[i + 1][j - 1][b | nums[i]]);
                    }
                }
            }
        }

        int maxVal = 0;
        for (int b = 0; b < (1 << 5); b++) {
            maxVal = Math.max(maxVal, b ^ dp[0][k][b]);
        }

        return maxVal;          
    }
}
