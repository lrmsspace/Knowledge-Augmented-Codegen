// Source: https://leetcode.com/problems/equal-row-and-column-pairs/   |   Difficulty: Medium
//
// Problem Description:
// Given a 0-indexed n x n integer matrix grid, return the number of pairs (ri, cj) such that row ri and column cj are equal.
//
// A row and column pair is considered equal if they contain the same elements in the same order (i.e., an equal array).
//
// Example:
// Input: grid = [[3,2,1],[1,7,6],[2,7,7]]
// Output: 1
// Explanation: There is 1 equal row and column pair:
// - (Row 2, Column 1): [2,7,7]
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 200
// 	1 <= grid[i][j] <= 105
//

class Solution {
    public int equalPairs(int[][] grid) {
        int n = grid.length;
        int count = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                boolean isEqual = true;
                for (int k = 0; k < n; k++) {
                    if (grid[i][k] != grid[k][j]) {
                        isEqual = false;
                        break;
                    }
                }
                if (isEqual) {
                    count++;
                }
            }
        }

        return count;           
    }
}
