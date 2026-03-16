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

int maxProduct(int* nums, int numsSize, int k, int limit) {
    int dp[numsSize + 1][2 * 100000 + 1];
    memset(dp, -1, sizeof(dp));
    dp[0][100000] = 1; // base case: empty subsequence with alternating sum 0 and product 1

    for (int i = 0; i < numsSize; ++i) {
        for (int j = 0; j <= 200000; ++j) {
            if (dp[i][j] == -1) continue;

            // Skip nums[i]
            if (dp[i + 1][j] < dp[i][j]) {
                dp[i + 1][j] = dp[i][j];
            }

            // Include nums[i] at even index
            int new_j_even = j + nums[i];
            if (new_j_even <= 200000) {
                long long new_product_even = (long long)dp[i][j] * nums[i];
                if (new_product_even <= limit && new_product_even > dp[i + 1][new_j_even]) {
                    dp[i + 1][new_j_even] = (int)new_product_even;
                }
            }

            // Include nums[i] at odd index
            int new_j_odd = j - nums[i];
            if (new_j_odd >= 0) {
                long long new_product_odd = (long long)dp[i][j] * nums[i];
                if (new_product_odd <= limit && new_product_odd > dp[i + 1][new_j_odd]) {
                    dp[i + 1][new_j_odd] = (int)new_product_odd;
                }
            }
        }
    }

    return dp[numsSize][k + 100000];        
}
