// Source: https://leetcode.com/problems/minimum-sum-of-values-by-dividing-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays nums and andValues of length n and m respectively.
//
// The value of an array is equal to the last element of that array.
//
// You have to divide nums into m disjoint contiguous subarrays such that for the ith subarray [li, ri], the bitwise AND of the subarray elements is equal to andValues[i], in other words, nums[li] & nums[li + 1] & ... & nums[ri] == andValues[i] for all 1 <= i <= m, where & represents the bitwise AND operator.
//
// Return the minimum possible sum of the values of the m subarrays nums is divided into. If it is not possible to divide nums into m subarrays satisfying these conditions, return -1.
//
// Example:
// Input: nums = [1,4,3,3,2], andValues = [0,3,3,2]
//
// Output: 12
//
// Explanation:
//
// The only possible way to divide nums is:
//
//
// 	[1,4] as 1 & 4 == 0.
// 	[3] as the bitwise AND of a single element subarray is that element itself.
// 	[3] as the bitwise AND of a single element subarray is that element itself.
// 	[2] as the bitwise AND of a single element subarray is that element itself.
//
//
// The sum of the values for these subarrays is 4 + 3 + 3 + 2 = 12.
//
// Constraints:
// 1 <= n == nums.length <= 104
// 	1 <= m == andValues.length <= min(n, 10)
// 	1 <= nums[i] < 105
// 	0 <= andValues[j] < 105
//

class Solution {
    public int minimumValueSum(int[] nums, int[] andValues) {
        int n = nums.length;
        int m = andValues.length;
        int[][] dp = new int[m + 1][n + 1];
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = Integer.MAX_VALUE;
            }
        }
        dp[0][0] = 0;

        for (int i = 1; i <= m; i++) {
            for (int j = i; j <= n; j++) {
                int currentAnd = -1;
                for (int k = j; k >= i; k--) {
                    currentAnd = (currentAnd == -1) ? nums[k - 1] : (currentAnd & nums[k - 1]);
                    if (currentAnd < andValues[i - 1]) {
                        break;
                    }
                    if (currentAnd == andValues[i - 1] && dp[i - 1][k - 1] != Integer.MAX_VALUE) {
                        dp[i][j] = Math.min(dp[i][j], dp[i - 1][k - 1] + nums[j - 1]);
                    }
                }
            }
        }

        return dp[m][n] == Integer.MAX_VALUE ? -1 : dp[m][n];           
    }
}
