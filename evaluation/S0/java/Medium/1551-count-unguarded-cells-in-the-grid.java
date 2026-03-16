// Source: https://leetcode.com/problems/count-unguarded-cells-in-the-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers m and n representing a 0-indexed m x n grid. You are also given two 2D integer arrays guards and walls where guards[i] = [rowi, coli] and walls[j] = [rowj, colj] represent the positions of the ith guard and jth wall respectively.
//
// A guard can see every cell in the four cardinal directions (north, east, south, or west) starting from their position unless obstructed by a wall or another guard. A cell is guarded if there is at least one guard that can see it.
//
// Return the number of unoccupied cells that are not guarded.
//
// Example:
// Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
// Output: 7
// Explanation: The guarded and unguarded cells are shown in red and green respectively in the above diagram.
// There are a total of 7 unguarded cells, so we return 7.
//
// Constraints:
// 1 <= m, n <= 105
// 	2 <= m * n <= 105
// 	1 <= guards.length, walls.length <= 5 * 104
// 	2 <= guards.length + walls.length <= m * n
// 	guards[i].length == walls[j].length == 2
// 	0 <= rowi, rowj < m
// 	0 <= coli, colj < n
// 	All the positions in guards and walls are unique.
//

class Solution {
    public int countUnguarded(int m, int n, int[][] guards, int[][] walls) {
        int[][] grid = new int[m][n];
        for (int[] wall : walls) {
            grid[wall[0]][wall[1]] = -1;
        }
        for (int[] guard : guards) {
            grid[guard[0]][guard[1]] = 1;
        }

        // Mark guarded cells
        for (int[] guard : guards) {
            int r = guard[0], c = guard[1];

            // Up
            for (int i = r - 1; i >= 0; i--) {
                if (grid[i][c] == -1 || grid[i][c] == 1) break;
                grid[i][c] = 2;
            }

            // Down
            for (int i = r + 1; i < m; i++) {
                if (grid[i][c] == -1 || grid[i][c] == 1) break;
                grid[i][c] = 2;
            }

            // Left
            for (int j = c - 1; j >= 0; j--) {
                if (grid[r][j] == -1 || grid[r][j] == 1) break;
                grid[r][j] = 2;
            }

            // Right
            for (int j = c + 1; j < n; j++) {
                if (grid[r][j] == -1 || grid[r][j] == 1) break;
                grid[r][j] = 2;
            }
        }

        // Count unguarded cells
        int unguardedCount = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    unguardedCount++;
                }
            }
        }

        return unguardedCount;          
    }
}
