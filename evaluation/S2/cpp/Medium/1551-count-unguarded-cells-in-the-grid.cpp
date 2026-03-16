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
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<int>> grid(m, vector<int>(n, 0));
        for (const auto& wall : walls) {
            grid[wall[0]][wall[1]] = -1; // Mark walls
        }
        for (const auto& guard : guards) {
            grid[guard[0]][guard[1]] = 1; // Mark guards
        }

        // Mark guarded cells
        for (const auto& guard : guards) {
            int r = guard[0], c = guard[1];
            // Mark north
            for (int i = r - 1; i >= 0 && grid[i][c] != -1 && grid[i][c] != 1; --i) {
                grid[i][c] = 2; // Mark as guarded
            }
            // Mark south
            for (int i = r + 1; i < m && grid[i][c] != -1 && grid[i][c] != 1; ++i) {
                grid[i][c] = 2; // Mark as guarded
            }
            // Mark west
            for (int j = c - 1; j >= 0 && grid[r][j] != -1 && grid[r][j] != 1; --j) {
                grid[r][j] = 2; // Mark as guarded
            }
            // Mark east
            for (int j = c + 1; j < n && grid[r][j] != -1 && grid[r][j] != 1; ++j) {
                grid[r][j] = 2; // Mark as guarded
            }
        }

        int unguardedCount = 0;
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                if (cell == 0) { // Unoccupied and not guarded
                    ++unguardedCount;
                }
            }
        }

        return unguardedCount;          
    }
};
