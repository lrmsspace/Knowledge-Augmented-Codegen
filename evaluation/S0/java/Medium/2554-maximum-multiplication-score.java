// Source: https://leetcode.com/problems/maximum-multiplication-score/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array a of size 4 and another integer array b of size at least 4.
//
// You need to choose 4 indices i0, i1, i2, and i3 from the array b such that i0 < i1 < i2 < i3. Your score will be equal to the value a[0] * b[i0] + a[1] * b[i1] + a[2] * b[i2] + a[3] * b[i3].
//
// Return the maximum score you can achieve.
//
// Example:
// Input: a = [3,2,5,6], b = [2,-6,4,-5,-3,2,-7]
//
// Output: 26
//
// Explanation:
// We can choose the indices 0, 1, 2, and 5. The score will be 3 * 2 + 2 * (-6) + 5 * 4 + 6 * 2 = 26.
//
// Constraints:
// a.length == 4
// 	4 <= b.length <= 105
// 	-105 <= a[i], b[i] <= 105
//

class Solution {
    public long maxScore(int[] a, int[] b) {
        int n = b.length;
        long[][] dp = new long[4][n];
        
        // Initialize the first row of dp with the first element of a
        dp[0][0] = (long)a[0] * b[0];
        for (int j = 1; j < n; j++) {
            dp[0][j] = Math.max(dp[0][j - 1], (long)a[0] * b[j]);
        }
        
        // Fill the dp table
        for (int i = 1; i < 4; i++) {
            for (int j = i; j < n; j++) {
                dp[i][j] = Math.max(dp[i][j - 1], dp[i - 1][j - 1] + (long)a[i] * b[j]);
            }
        }
        
        return dp[3][n - 1];            
    }
}
