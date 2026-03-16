// Source: https://leetcode.com/problems/check-knight-tour-configuration/   |   Difficulty: Medium
//
// Problem Description:
// There is a knight on an n x n chessboard. In a valid configuration, the knight starts at the top-left cell of the board and visits every cell on the board exactly once.
//
// You are given an n x n integer matrix grid consisting of distinct integers from the range [0, n * n - 1] where grid[row][col] indicates that the cell (row, col) is the grid[row][col]th cell that the knight visited. The moves are 0-indexed.
//
// Return true if grid represents a valid configuration of the knight's movements or false otherwise.
//
// Note that a valid knight move consists of moving two squares vertically and one square horizontally, or two squares horizontally and one square vertically. The figure below illustrates all the possible eight moves of a knight from some cell.
//
// Example:
// Input: grid = [[0,11,16,5,20],[17,4,19,10,15],[12,1,8,21,6],[3,18,23,14,9],[24,13,2,7,22]]
// Output: true
// Explanation: The above diagram represents the grid. It can be shown that it is a valid configuration.
//
// Constraints:
// n == grid.length == grid[i].length
// 	3 <= n <= 7
// 	0 <= grid[row][col] < n * n
// 	All integers in grid are unique.
//

class Solution {
public:
    bool checkValidGrid(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<pair<int, int>> moves = {
            {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
            {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
        };

        // Create a mapping from move index to its position
        vector<pair<int, int>> position(n * n);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                position[grid[r][c]] = {r, c};
            }
        }

        // Check each consecutive move
        for (int i = 0; i < n * n - 1; ++i) {
            auto [r1, c1] = position[i];
            auto [r2, c2] = position[i + 1];
            bool validMove = false;

            for (const auto& [dr, dc] : moves) {
                if (r1 + dr == r2 && c1 + dc == c2) {
                    validMove = true;
                    break;
                }
            }

            if (!validMove) {
                return false;
            }
        }

        return true;            
    }
};
