// Source: https://leetcode.com/problems/maximal-square/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.
//
// Example:
// Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
// Output: 4
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 300
// 	matrix[i][j] is '0' or '1'.
//

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        int maxSide = 0;

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (matrix[i - 1][j - 1] == '1') {
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                    maxSide = max(maxSide, dp[i][j]);
                }
            }
        }

        return maxSide * maxSide;           
    }
};
