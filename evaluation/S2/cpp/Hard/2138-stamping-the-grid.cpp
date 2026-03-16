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
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - 0-1 BFS (graph, queue, 01-bfs, bfs)
//   • When to use: Use when finding shortest paths in a graph where edge weights are restricted to only 0 or 1. It efficiently determines minimum distances from a source to all reachable nodes, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds shortest paths from a single source in a graph where all edge weights are either 0 or 1. It achieves this in O(V + E) time complexity by using a deque to prioritize 0-weight edges.
//   • Invariants: All nodes in the deque have a distance value less than or equal to any node not yet processed.; Nodes added to the front of the deque (0-weight edges) always have a distance equal to the node they came from.
//   • Tips: Use a deque to maintain order: 0-weight edges go to front, 1-weight edges to back.; Initialize distances to infinity and source distance to 0.
//   • Pitfalls: Forgetting to update distances for 0-weight edges before adding to deque front.; Incorrectly handling visited states, leading to TLE or incorrect paths.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> heights(m, vector<int>(n, 0));

        // Compute heights of consecutive zeros for each column
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                if (grid[i][j] == 0) {
                    heights[i][j] = (i > 0 ? heights[i - 1][j] : 0) + 1;
                }
            }
        }

        // Check if we can place stamps
        for (int i = stampHeight - 1; i < m; ++i) {
            for (int j = stampWidth - 1; j < n; ++j) {
                if (heights[i][j] >= stampHeight && heights[i][j - stampWidth + 1] >= stampHeight) {
                    // Mark the area covered by the stamp
                    for (int k = 0; k < stampHeight; ++k) {
                        for (int l = 0; l < stampWidth; ++l) {
                            grid[i - k][j - l] = 2; // Mark as covered
                        }
                    }
                }
            }
        }

        // Check if all empty cells are covered
        for (const auto& row : grid) {
            for (int cell : row) {
                if (cell == 0) return false;
            }
        }

        return true;            
    }
};
