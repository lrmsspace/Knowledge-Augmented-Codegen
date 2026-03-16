// Source: https://leetcode.com/problems/maximum-sum-with-at-most-k-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer matrix grid of size n x m, an integer array limits of length n, and an integer k. The task is to find the maximum sum of at most k elements from the matrix grid such that:
//
//
// 	
// 	The number of elements taken from the ith row of grid does not exceed limits[i].
// 	
//
//
// Return the maximum sum.
//
// Example:
// Input: grid = [[1,2],[3,4]], limits = [1,2], k = 2
//
// Output: 7
//
// Explanation:
//
//
// 	From the second row, we can take at most 2 elements. The elements taken are 4 and 3.
// 	The maximum possible sum of at most 2 selected elements is 4 + 3 = 7.
//
// Constraints:
// n == grid.length == limits.length
// 	m == grid[i].length
// 	1 <= n, m <= 500
// 	0 <= grid[i][j] <= 105
// 	0 <= limits[i] <= m
// 	0 <= k <= min(n * m, sum(limits))
//

class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        for (int i = 1; i <= n; ++i) {
            vector<int>& row = grid[i - 1];
            sort(row.rbegin(), row.rend());

            vector<long long> prefixSums(limits[i - 1] + 1, 0);
            for (int j = 1; j <= limits[i - 1]; ++j) {
                prefixSums[j] = prefixSums[j - 1] + row[j - 1];
            }

            for (int j = 0; j <= k; ++j) {
                dp[i][j] = dp[i - 1][j]; // Not taking any element from this row
                for (int x = 1; x <= limits[i - 1] && x <= j; ++x) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - x] + prefixSums[x]);
                }
            }
        }

        return dp[n][k];            
    }
};
