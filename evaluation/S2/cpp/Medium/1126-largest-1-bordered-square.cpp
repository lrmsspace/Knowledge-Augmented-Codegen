// Source: https://leetcode.com/problems/largest-1-bordered-square/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D grid of 0s and 1s, return the number of elements in the largest square subgrid that has all 1s on its border, or 0 if such a subgrid doesn't exist in the grid.
//
// Example:
// Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
// Output: 9
//
// Constraints:
// 1 <= grid.length <= 100
// 	1 <= grid[0].length <= 100
// 	grid[i][j] is 0 or 1
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> right(m, vector<int>(n)), down(m, vector<int>(n));
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (grid[i][j] == 1) {
                    right[i][j] = (j + 1 < n ? right[i][j + 1] : 0) + 1;
                    down[i][j] = (i + 1 < m ? down[i + 1][j] : 0) + 1;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int len = min(right[i][j], down[i][j]);
                while (len > ans) {
                    if (right[i + len - 1][j] >= len && down[i][j + len - 1] >= len) {
                        ans = len;
                    }
                    --len;
                }
            }
        }
        return ans * ans;           
    }
};
