// Source: https://leetcode.com/problems/minimum-operations-to-write-the-letter-y-on-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed n x n grid where n is odd, and grid[r][c] is 0, 1, or 2.
//
// We say that a cell belongs to the Letter Y if it belongs to one of the following:
//
//
// 	The diagonal starting at the top-left cell and ending at the center cell of the grid.
// 	The diagonal starting at the top-right cell and ending at the center cell of the grid.
// 	The vertical line starting at the center cell and ending at the bottom border of the grid.
//
//
// The Letter Y is written on the grid if and only if:
//
//
// 	All values at cells belonging to the Y are equal.
// 	All values at cells not belonging to the Y are equal.
// 	The values at cells belonging to the Y are different from the values at cells not belonging to the Y.
//
//
// Return the minimum number of operations needed to write the letter Y on the grid given that in one operation you can change the value at any cell to 0, 1, or 2.
//
// Example:
// Input: grid = [[1,2,2],[1,1,0],[0,1,0]]
// Output: 3
// Explanation: We can write Y on the grid by applying the changes highlighted in blue in the image above. After the operations, all cells that belong to Y, denoted in bold, have the same value of 1 while those that do not belong to Y are equal to 0.
// It can be shown that 3 is the minimum number of operations needed to write Y on the grid.
//
// Constraints:
// 3 <= n <= 49 
// 	n == grid.length == grid[i].length
// 	0 <= grid[i][j] <= 2
// 	n is odd.
//

class Solution {
public:
    int minimumOperationsToWriteY(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> countY(3, 0);
        vector<int> countNotY(3, 0);
        
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                bool isY = (c == n / 2 && r >= n / 2) || (r == c && r <= n / 2) || (r + c == n - 1 && r <= n / 2);
                if (isY) {
                    countY[grid[r][c]]++;
                } else {
                    countNotY[grid[r][c]]++;
                }
            }
        }
        
        int totalY = (n + 1) / 2 + (n / 2) * 2;
        int totalNotY = n * n - totalY;
        int minOperations = INT_MAX;
        
        for (int yVal = 0; yVal < 3; ++yVal) {
            for (int notYVal = 0; notYVal < 3; ++notYVal) {
                if (yVal != notYVal) {
                    int operations = (totalY - countY[yVal]) + (totalNotY - countNotY[notYVal]);
                    minOperations = min(minOperations, operations);
                }
            }
        }
        
        return minOperations;           
    }
};
