// Source: https://leetcode.com/problems/sort-matrix-by-diagonals/   |   Difficulty: Medium
//
// Problem Description:
// You are given an n x n square matrix of integers grid. Return the matrix such that:
//
//
// 	The diagonals in the bottom-left triangle (including the middle diagonal) are sorted in non-increasing order.
// 	The diagonals in the top-right triangle are sorted in non-decreasing order.
//
// Example:
// Input: grid = [[1,7,3],[9,8,2],[4,5,6]]
//
// Output: [[8,2,3],[9,6,7],[4,5,1]]
//
// Explanation:
//
//
//
// The diagonals with a black arrow (bottom-left triangle) should be sorted in non-increasing order:
//
//
// 	[1, 8, 6] becomes [8, 6, 1].
// 	[9, 5] and [4] remain unchanged.
//
//
// The diagonals with a blue arrow (top-right triangle) should be sorted in non-decreasing order:
//
//
// 	[7, 2] becomes [2, 7].
// 	[3] remains unchanged.
//
// Constraints:
// grid.length == grid[i].length == n
// 	1 <= n <= 10
// 	-105 <= grid[i][j] <= 105
//

class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size();

        // Sort bottom-left diagonals (including middle diagonal)
        for (int col = 0; col < n; ++col) {
            vector<int> diagonal;
            int r = 0, c = col;
            while (r < n && c >= 0) {
                diagonal.push_back(grid[r][c]);
                ++r; --c;
            }
            sort(diagonal.rbegin(), diagonal.rend());
            r = 0; c = col;
            for (int val : diagonal) {
                grid[r][c] = val;
                ++r; --c;
            }
        }
        for (int row = 1; row < n; ++row) {
            vector<int> diagonal;
            int r = row, c = n - 1;
            while (r < n && c >= 0) {
                diagonal.push_back(grid[r][c]);
                ++r; --c;
            }
            sort(diagonal.rbegin(), diagonal.rend());
            r = row; c = n - 1;
            for (int val : diagonal) {
                grid[r][c] = val;
                ++r; --c;
            }
        }

        // Sort top-right diagonals
        for (int row = 0; row < n; ++row) {
            vector<int> diagonal;
            int r = row, c = 0;
            while (r >= 0 && c < n) {
                diagonal.push_back(grid[r][c]);
                --r; ++c;
            }
            sort(diagonal.begin(), diagonal.end());
            r = row; c = 0;
            for (int val : diagonal) {
                grid[r][c] = val;
                --r; ++c;
            }
        }
        for (int col = 1; col < n; ++col) {
            vector<int> diagonal;
            int r = n - 1, c = col;
            while (r >= 0 && c < n) {
                diagonal.push_back(grid[r][c]);
                --r; ++c;
            }
            sort(diagonal.begin(), diagonal.end());
            r = n - 1; c = col;
            for (int val : diagonal) {
                grid[r][c] = val;
                --r; ++c;
            }
        }

        return grid;            
    }
};
