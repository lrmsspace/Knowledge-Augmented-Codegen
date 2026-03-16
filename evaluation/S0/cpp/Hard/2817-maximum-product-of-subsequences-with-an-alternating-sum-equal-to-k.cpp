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
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        int n = nums.size();
        vector<vector<long long>> dp(n + 1, vector<long long>(2 * 100000 + 1, -1));
        dp[0][100000] = 1;  // Base case: empty subsequence with alternating sum 0 and product 1

        for (int i = 1; i <= n; ++i) {
            int num = nums[i - 1];
            for (int j = 0; j <= 2 * 100000; ++j) {
                // Not take nums[i-1]
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);

                // Take nums[i-1] at even index
                if (j - num >= 0 && dp[i - 1][j - num] != -1) {
                    long long newProduct = dp[i - 1][j - num] * num;
                    if (newProduct <= limit) {
                        dp[i][j] = max(dp[i][j], newProduct);
                    }
                }

                // Take nums[i-1] at odd index
                if (j + num <= 2 * 100000 && dp[i - 1][j + num] != -1) {
                    long long newProduct = dp[i - 1][j + num] * num;
                    if (newProduct <= limit) {
                        dp[i][j] = max(dp[i][j], newProduct);
                    }
                }
            }
        }

        return dp[n][k + 100000] == -1 ? -1 : (int)dp[n][k + 100000];           
    }
};
