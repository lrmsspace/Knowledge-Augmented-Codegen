// Source: https://leetcode.com/problems/stamping-the-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n binary matrix grid where each cell is either 0 (empty) or 1 (occupied).
//
// You are then given stamps of size stampHeight x stampWidth. We want to fit the stamps such that they follow the given restrictions and requirements:
//
//
// 	Cover all the empty cells.
// 	Do not cover any of the occupied cells.
// 	We can put as many stamps as we want.
// 	Stamps can overlap with each other.
// 	Stamps are not allowed to be rotated.
// 	Stamps must stay completely inside the grid.
//
//
// Return true if it is possible to fit the stamps while following the given restrictions and requirements. Otherwise, return false.
//
// Example:
// Input: grid = [[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0]], stampHeight = 4, stampWidth = 3
// Output: true
// Explanation: We have two overlapping stamps (labeled 1 and 2 in the image) that are able to cover all the empty cells.
//
// Constraints:
// m == grid.length
// 	n == grid[r].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 2 * 105
// 	grid[r][c] is either 0 or 1.
// 	1 <= stampHeight, stampWidth <= 105
//

class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        int m = grid.size();
        int n = grid[0].size();
        
        vector<vector<int>> prefixSum(m + 1, vector<int>(n + 1, 0));
        
        // Build prefix sum of occupied cells
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                prefixSum[i][j] = grid[i - 1][j - 1] + prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
            }
        }
        
        vector<vector<int>> stampable(m, vector<int>(n, 0));
        
        // Determine stampable positions
        for (int i = 0; i <= m - stampHeight; i++) {
            for (int j = 0; j <= n - stampWidth; j++) {
                int total = prefixSum[i + stampHeight][j + stampWidth] - prefixSum[i][j + stampWidth] - prefixSum[i + stampHeight][j] + prefixSum[i][j];
                if (total == 0) {
                    stampable[i][j] = 1;
                }
            }
        }
        
        // Build prefix sum of stampable positions
        vector<vector<int>> stampPrefixSum(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                stampPrefixSum[i][j] = stampable[i - 1][j - 1] + stampPrefixSum[i - 1][j] + stampPrefixSum[i][j - 1] - stampPrefixSum[i - 1][j - 1];
            }
        }
        
        // Check if all empty cells can be covered
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    int r1 = max(0, i - stampHeight + 1);
                    int c1 = max(0, j - stampWidth + 1);
                    int r2 = i;
                    int c2 = j;
                    
                    int totalStamps = stampPrefixSum[r2 + 1][c2 + 1] - stampPrefixSum[r1][c2 + 1] - stampPrefixSum[r2 + 1][c1] + stampPrefixSum[r1][c1];
                    
                    if (totalStamps == 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};
