// Source: https://leetcode.com/problems/maximum-difference-score-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix grid consisting of positive integers. You can move from a cell in the matrix to any other cell that is either to the bottom or to the right (not necessarily adjacent). The score of a move from a cell with the value c1 to a cell with the value c2 is c2 - c1.
//
// You can start at any cell, and you have to make at least one move.
//
// Return the maximum total score you can achieve.
//
// Example:
// Input: grid = [[9,5,7,3],[8,9,6,1],[6,7,14,3],[2,5,3,1]]
//
// Output: 9
//
// Explanation: We start at the cell (0, 1), and we perform the following moves:
// - Move from the cell (0, 1) to (2, 1) with a score of 7 - 5 = 2.
// - Move from the cell (2, 1) to (2, 2) with a score of 14 - 7 = 7.
// The total score is 2 + 7 = 9.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 1000
// 	4 <= m * n <= 105
// 	1 <= grid[i][j] <= 105
//

class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int maxScore = INT_MIN;

        // Precompute the maximum values for each cell from bottom-right to top-left
        vector<vector<int>> maxFromBottomRight(m, vector<int>(n, 0));
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int currentValue = grid[i][j];
                int maxValue = INT_MIN;

                if (i + 1 < m) {
                    maxValue = max(maxValue, maxFromBottomRight[i + 1][j]);
                }
                if (j + 1 < n) {
                    maxValue = max(maxValue, maxFromBottomRight[i][j + 1]);
                }

                if (maxValue != INT_MIN) {
                    maxFromBottomRight[i][j] = maxValue;
                } else {
                    maxFromBottomRight[i][j] = currentValue;
                }
            }
        }

        // Calculate the maximum score
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int currentValue = grid[i][j];
                if (i + 1 < m) {
                    maxScore = max(maxScore, maxFromBottomRight[i + 1][j] - currentValue);
                }
                if (j + 1 < n) {
                    maxScore = max(maxScore, maxFromBottomRight[i][j + 1] - currentValue);
                }
            }
        }

        return maxScore;            
    }
};
