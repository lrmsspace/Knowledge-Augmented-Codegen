// Source: https://leetcode.com/problems/strange-printer-ii/   |   Difficulty: Hard
//
// Problem Description:
// There is a strange printer with the following two special requirements:
//
//
// 	On each turn, the printer will print a solid rectangular pattern of a single color on the grid. This will cover up the existing colors in the rectangle.
// 	Once the printer has used a color for the above operation, the same color cannot be used again.
//
//
// You are given a m x n matrix targetGrid, where targetGrid[row][col] is the color in the position (row, col) of the grid.
//
// Return true if it is possible to print the matrix targetGrid, otherwise, return false.
//
// Example:
// Input: targetGrid = [[1,1,1,1],[1,2,2,1],[1,2,2,1],[1,1,1,1]]
// Output: true
//
// Constraints:
// m == targetGrid.length
// 	n == targetGrid[i].length
// 	1 <= m, n <= 60
// 	1 <= targetGrid[row][col] <= 60
//

class Solution {
public:
    bool isPrintable(vector<vector<int>>& targetGrid) {
        int m = targetGrid.size();
        int n = targetGrid[0].size();
        vector<vector<int>> bounds(61, vector<int>{m, n, -1, -1}); // minRow, minCol, maxRow, maxCol
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int color = targetGrid[i][j];
                bounds[color][0] = min(bounds[color][0], i);
                bounds[color][1] = min(bounds[color][1], j);
                bounds[color][2] = max(bounds[color][2], i);
                bounds[color][3] = max(bounds[color][3], j);
            }
        }
        
        vector<bool> printed(61, false);
        bool changed = true;
        
        while (changed) {
            changed = false;
            for (int color = 1; color <= 60; ++color) {
                if (printed[color]) continue;
                
                int minRow = bounds[color][0];
                int minCol = bounds[color][1];
                int maxRow = bounds[color][2];
                int maxCol = bounds[color][3];
                
                if (minRow > maxRow) { // Color not present
                    printed[color] = true;
                    changed = true;
                    continue;
                }
                
                bool canPrint = true;
                for (int i = minRow; i <= maxRow && canPrint; ++i) {
                    for (int j = minCol; j <= maxCol; ++j) {
                        if (targetGrid[i][j] != color && !printed[targetGrid[i][j]]) {
                            canPrint = false;
                            break;
                        }
                    }
                }
                
                if (canPrint) {
                    printed[color] = true;
                    changed = true;
                }
            }
        }
        
        for (int color = 1; color <= 60; ++color) {
            if (!printed[color]) return false;
        }
        
        return true;            
    }
};
