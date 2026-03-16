// Source: https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums and multipliers of size n and m respectively, where n >= m.
//
// You begin with a score of 0. You want to perform exactly m operations. On the ith operation (0-indexed) you will:
//
//
//     Choose one integer x from either the start or the end of the array nums.
//     Add multipliers[i] * x to your score.
//     
//         Note that multipliers[0] corresponds to the first operation, multipliers[1] to the second operation, and so on.
//     
//     
//     Remove x from nums.
//
//
// Return the maximum score after performing m operations.
//
// Example:
// Input: nums = [1,2,3], multipliers = [3,2,1]
// Output: 14
// Explanation: An optimal solution is as follows:
// - Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
// - Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
// - Choose from the end, [1], adding 1 * 1 = 1 to the score.
// The total score is 9 + 4 + 1 = 14.
//
// Constraints:
// n == nums.length
// 	m == multipliers.length
// 	1 <= m <= 300
// 	m <= n <= 105 
// 	-1000 <= nums[i], multipliers[i] <= 1000
//

class Solution {
    public int maximumScore(int[] nums, int[] multipliers) {
        int m = multipliers.length;
        int n = nums.length;
        int[][] dp = new int[m + 1][m + 1];

        for (int i = m - 1; i >= 0; i--) {
            for (int left = i; left >= 0; left--) {
                int mult = multipliers[i];
                int right = n - 1 - (i - left);
                dp[i][left] = Math.max(
                    mult * nums[left] + dp[i + 1][left + 1],
                    mult * nums[right] + dp[i + 1][left]
                );
            }
        }

        return dp[0][0];            
    }
}
