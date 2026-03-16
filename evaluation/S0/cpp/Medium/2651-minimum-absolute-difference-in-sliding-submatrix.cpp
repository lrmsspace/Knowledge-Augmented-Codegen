// Source: https://leetcode.com/problems/minimum-absolute-difference-in-sliding-submatrix/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid and an integer k.
//
// For every contiguous k x k submatrix of grid, compute the minimum absolute difference between any two distinct values within that submatrix.
//
// Return a 2D array ans of size (m - k + 1) x (n - k + 1), where ans[i][j] is the minimum absolute difference in the submatrix whose top-left corner is (i, j) in grid.
//
// Note: If all elements in the submatrix have the same value, the answer will be 0.
// A submatrix (x1, y1, x2, y2) is a matrix that is formed by choosing all cells matrix[x][y] where x1 <= x <= x2 and y1 <= y <= y2.
//
// Example:
// Input: grid = [[1,8],[3,-2]], k = 2
//
// Output: [[2]]
//
// Explanation:
//
//
// 	There is only one possible k x k submatrix: [[1, 8], [3, -2]].
// 	Distinct values in the submatrix are [1, 8, 3, -2].
// 	The minimum absolute difference in the submatrix is |1 - 3| = 2. Thus, the answer is [[2]].
//
// Constraints:
// 1 <= m == grid.length <= 30
// 	1 <= n == grid[i].length <= 30
// 	-105 <= grid[i][j] <= 105
// 	1 <= k <= min(m, n)
//

class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> result(m - k + 1, vector<int>(n - k + 1, 0));

        for (int i = 0; i <= m - k; ++i) {
            for (int j = 0; j <= n - k; ++j) {
                set<int> values;
                for (int x = i; x < i + k; ++x) {
                    for (int y = j; y < j + k; ++y) {
                        values.insert(grid[x][y]);
                    }
                }

                int minDiff = INT_MAX;
                int prev = INT_MIN;
                for (int val : values) {
                    if (prev != INT_MIN) {
                        minDiff = min(minDiff, val - prev);
                    }
                    prev = val;
                }

                result[i][j] = (minDiff == INT_MAX) ? 0 : minDiff;
            }
        }

        return result;          
    }
};
