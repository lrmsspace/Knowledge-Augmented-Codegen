// Source: https://leetcode.com/problems/making-a-large-island/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
//
// Return the size of the largest island in grid after applying this operation.
//
// An island is a 4-directionally connected group of 1s.
//
// Example:
// Input: grid = [[1,0],[0,1]]
// Output: 3
// Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 500
// 	grid[i][j] is either 0 or 1.
//

class Solution {
    public int largestIsland(int[][] grid) {
        int n = grid.length;
        int color = 2;
        Map<Integer, Integer> areaMap = new HashMap<>();
        int maxArea = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int area = dfs(grid, i, j, color);
                    areaMap.put(color, area);
                    maxArea = Math.max(maxArea, area);
                    color++;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    Set<Integer> neighborColors = new HashSet<>();
                    if (i > 0 && grid[i - 1][j] > 1) neighborColors.add(grid[i - 1][j]);
                    if (i < n - 1 && grid[i + 1][j] > 1) neighborColors.add(grid[i + 1][j]);
                    if (j > 0 && grid[i][j - 1] > 1) neighborColors.add(grid[i][j - 1]);
                    if (j < n - 1 && grid[i][j + 1] > 1) neighborColors.add(grid[i][j + 1]);

                    int newArea = 1;
                    for (int c : neighborColors) {
                        newArea += areaMap.get(c);
                    }
                    maxArea = Math.max(maxArea, newArea);
                }
            }
        }

        return maxArea == 0 ? n * n : maxArea;          
    }
}
