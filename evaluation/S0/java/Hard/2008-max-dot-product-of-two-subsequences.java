// Source: https://leetcode.com/problems/max-dot-product-of-two-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// Given two arrays nums1 and nums2.
//
// Return the maximum dot product between non-empty subsequences of nums1 and nums2 with the same length.
//
// A subsequence of a array is a new array which is formed from the original array by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, [2,3,5] is a subsequence of [1,2,3,4,5] while [1,5,3] is not).
//
// Example:
// Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
// Output: 18
// Explanation: Take subsequence [2,-2] from nums1 and subsequence [3,-6] from nums2.
// Their dot product is (2*3 + (-2)*(-6)) = 18.
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 500
// 	-1000 <= nums1[i], nums2[i] <= 1000
//

class Solution {
    public int maxDotProduct(int[] nums1, int[] nums2) {
        int n = nums1.length;
        int m = nums2.length;
        int[][] dp = new int[n + 1][m + 1];

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int prod = nums1[i - 1] * nums2[j - 1];
                dp[i][j] = Math.max(prod, Math.max(dp[i - 1][j - 1] + prod, Math.max(dp[i - 1][j], dp[i][j - 1])));
            }
        }

        return dp[n][m];                    
    }
}
