// Source: https://leetcode.com/problems/regions-cut-by-slashes/   |   Difficulty: Medium
//
// Problem Description:
// An n x n grid is composed of 1 x 1 squares where each 1 x 1 square consists of a '/', '\', or blank space ' '. These characters divide the square into contiguous regions.
//
// Given the grid grid represented as a string array, return the number of regions.
//
// Note that backslash characters are escaped, so a '\' is represented as '\\'.
//
// Example:
// Input: grid = [" /","/ "]
// Output: 2
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 30
// 	grid[i][j] is either '/', '\', or ' '.
//

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size();
        int size = n * 3;
        vector<vector<int>> expanded(size, vector<int>(size, 0));

        // Expand the grid
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '/') {
                    expanded[i * 3][j * 3 + 2] = 1;
                    expanded[i * 3 + 1][j * 3 + 1] = 1;
                    expanded[i * 3 + 2][j * 3] = 1;
                } else if (grid[i][j] == '\\') {
                    expanded[i * 3][j * 3] = 1;
                    expanded[i * 3 + 1][j * 3 + 1] = 1;
                    expanded[i * 3 + 2][j * 3 + 2] = 1;
                }
            }
        }

        // DFS to count regions
        int regions = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (expanded[i][j] == 0) {
                    ++regions;
                    dfs(expanded, i, j, size);
                }
            }
        }

        return regions;         
    }
};
