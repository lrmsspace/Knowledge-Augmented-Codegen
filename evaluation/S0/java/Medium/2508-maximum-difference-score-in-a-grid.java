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
    public int maxScore(List<List<Integer>> grid) {
        int m = grid.size();
        int n = grid.get(0).size();
        int maxScore = Integer.MIN_VALUE;

        int[][] maxFromBottomRight = new int[m + 1][n + 1];

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                maxFromBottomRight[i][j] = Math.max(
                    Math.max(maxFromBottomRight[i + 1][j], maxFromBottomRight[i][j + 1]),
                    grid.get(i).get(j)
                );
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int currentValue = grid.get(i).get(j);
                int potentialMax = maxFromBottomRight[i + 1][j] - currentValue;
                potentialMax = Math.max(potentialMax, maxFromBottomRight[i][j + 1] - currentValue);
                maxScore = Math.max(maxScore, potentialMax);
            }
        }

        return maxScore;            
    }
}
