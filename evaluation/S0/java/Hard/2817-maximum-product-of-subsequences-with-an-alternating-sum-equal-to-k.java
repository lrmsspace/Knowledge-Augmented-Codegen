// Source: https://leetcode.com/problems/maximum-product-of-subsequences-with-an-alternating-sum-equal-to-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers, k and limit. Your task is to find a non-empty subsequence of nums that:
//
//
// 	Has an alternating sum equal to k.
// 	Maximizes the product of all its numbers without the product exceeding limit.
//
//
// Return the product of the numbers in such a subsequence. If no subsequence satisfies the requirements, return -1.
//
// The alternating sum of a 0-indexed array is defined as the sum of the elements at even indices minus the sum of the elements at odd indices.
//
// Example:
// Input: nums = [1,2,3], k = 2, limit = 10
//
// Output: 6
//
// Explanation:
//
// The subsequences with an alternating sum of 2 are:
//
//
// 	[1, 2, 3]
//
// 	
// 		Alternating Sum: 1 - 2 + 3 = 2
// 		Product: 1 * 2 * 3 = 6
// 	
// 	
// 	[2]
// 	
// 		Alternating Sum: 2
// 		Product: 2
// 	
// 	
//
//
// The maximum product within the limit is 6.
//
// Constraints:
// 1 <= nums.length <= 150
// 	0 <= nums[i] <= 12
// 	-105 <= k <= 105
// 	1 <= limit <= 5000
//

class Solution {
    public int maxProduct(int[] nums, int k, int limit) {
        int n = nums.length;
        long[][][] dp = new long[n + 1][2 * 100000 + 1][2];
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= 2 * 100000; j++) {
                dp[i][j][0] = -1;
                dp[i][j][1] = -1;
            }
        }
        dp[0][100000][0] = 1;

        for (int i = 1; i <= n; i++) {
            int num = nums[i - 1];
            for (int j = 0; j <= 2 * 100000; j++) {
                for (int p = 0; p < 2; p++) {
                    if (dp[i - 1][j][p] != -1) {
                        dp[i][j][p] = Math.max(dp[i][j][p], dp[i - 1][j][p]);
                        int newJ = p == 0 ? j + num : j - num;
                        if (newJ >= 0 && newJ <= 2 * 100000) {
                            long newProduct = dp[i - 1][j][p] * num;
                            if (newProduct <= limit) {
                                dp[i][newJ][1 - p] = Math.max(dp[i][newJ][1 - p], newProduct);
                            }
                        }
                    }
                }
            }
        }

        long result = Math.max(dp[n][k + 100000][0], dp[n][k + 100000][1]);
        return result == -1 ? -1 : (int) result;            
    }
}
