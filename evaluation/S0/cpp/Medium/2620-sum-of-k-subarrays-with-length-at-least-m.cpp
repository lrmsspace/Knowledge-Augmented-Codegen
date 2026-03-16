// Source: https://leetcode.com/problems/sum-of-k-subarrays-with-length-at-least-m/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and two integers, k and m.
//
// Return the maximum sum of k non-overlapping subarrays of nums, where each subarray has a length of at least m.
//
// Example:
// Input: nums = [1,2,-1,3,3,4], k = 2, m = 2
//
// Output: 13
//
// Explanation:
//
// The optimal choice is:
//
//
// 	Subarray nums[3..5] with sum 3 + 3 + 4 = 10 (length is 3 >= m).
// 	Subarray nums[0..1] with sum 1 + 2 = 3 (length is 2 >= m).
//
//
// The total sum is 10 + 3 = 13.
//
// Constraints:
// 1 <= nums.length <= 2000
// 	-104 <= nums[i] <= 104
// 	1 <= k <= floor(nums.length / m)
// 	1 <= m <= 3
//

class Solution {
public:
    int maxSum(vector<int>& nums, int k, int m) {
        int n = nums.size();
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        vector<vector<int>> dp(k + 1, vector<int>(n + 1, INT_MIN));
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = 0;
        }

        for (int i = 1; i <= k; ++i) {
            for (int j = i * m; j <= n; ++j) {
                for (int length = m; length <= j - (i - 1) * m + 1; ++length) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - length] + prefixSum[j] - prefixSum[j - length]);
                }
            }
        }

        return dp[k][n];            
    }
};
