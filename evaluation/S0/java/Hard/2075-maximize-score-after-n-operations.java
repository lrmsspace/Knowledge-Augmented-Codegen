// Source: https://leetcode.com/problems/maximize-score-after-n-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given nums, an array of positive integers of size 2 * n. You must perform n operations on this array.
//
// In the ith operation (1-indexed), you will:
//
//
// 	Choose two elements, x and y.
// 	Receive a score of i * gcd(x, y).
// 	Remove x and y from nums.
//
//
// Return the maximum score you can receive after performing n operations.
//
// The function gcd(x, y) is the greatest common divisor of x and y.
//
// Example:
// Input: nums = [1,2]
// Output: 1
// Explanation: The optimal choice of operations is:
// (1 * gcd(1, 2)) = 1
//
// Constraints:
// 1 <= n <= 7
// 	nums.length == 2 * n
// 	1 <= nums[i] <= 106
//

class Solution {
    public int maxScore(int[] nums) {
        int n = nums.length;
        int N = n / 2;
        int[][] gcd = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                gcd[i][j] = gcd(nums[i], nums[j]);
            }
        }

        int[] dp = new int[1 << n];
        for (int mask = 0; mask < (1 << n); mask++) {
            int bits = Integer.bitCount(mask);
            if (bits % 2 != 0) continue;
            int op = bits / 2 + 1;
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) != 0) continue;
                for (int j = i + 1; j < n; j++) {
                    if ((mask & (1 << j)) != 0) continue;
                    int newMask = mask | (1 << i) | (1 << j);
                    dp[newMask] = Math.max(dp[newMask], dp[mask] + op * gcd[i][j]);
                }
            }
        }
        return dp[(1 << n) - 1];            
    }
}
