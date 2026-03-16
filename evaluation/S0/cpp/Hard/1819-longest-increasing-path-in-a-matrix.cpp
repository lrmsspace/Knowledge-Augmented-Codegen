// Source: https://leetcode.com/problems/longest-increasing-path-in-a-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n integers matrix, return the length of the longest increasing path in matrix.
//
// From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).
//
// Example:
// Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
// Output: 4
// Explanation: The longest increasing path is [1, 2, 6, 9].
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 200
// 	0 <= matrix[i][j] <= 231 - 1
//

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        function<int(int, int)> dfs = [&](int x, int y) {
            if (dp[x][y] != 0) return dp[x][y];
            int maxLength = 1;
            vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            for (auto& dir : directions) {
                int newX = x + dir.first;
                int newY = y + dir.second;
                if (newX >= 0 && newX < m && newY >= 0 && newY < n && matrix[newX][newY] > matrix[x][y]) {
                    maxLength =         
    }
};
