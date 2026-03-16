// Source: https://leetcode.com/problems/zigzag-grid-traversal-with-skip/   |   Difficulty: Easy
//
// Problem Description:
// You are given an m x n 2D array grid of positive integers.
//
// Your task is to traverse grid in a zigzag pattern while skipping every alternate cell.
//
// Zigzag pattern traversal is defined as following the below actions:
//
//
// 	Start at the top-left cell (0, 0).
// 	Move right within a row until the end of the row is reached.
// 	Drop down to the next row, then traverse left until the beginning of the row is reached.
// 	Continue alternating between right and left traversal until every row has been traversed.
//
//
// Note that you must skip every alternate cell during the traversal.
//
// Return an array of integers result containing, in order, the value of the cells visited during the zigzag traversal with skips.
//
// Example:
// Input: grid = [[1,2],[3,4]]
//
// Output: [1,4]
//
// Explanation:
//
// Constraints:
// 2 <= n == grid.length <= 50
// 	2 <= m == grid[i].length <= 50
// 	1 <= grid[i][j] <= 2500
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> zigzagTraversal(vector<vector<int>>& grid) {
        vector<int> result;
        int rows = grid.size();
        int cols = grid[0].size();
        bool leftToRight = true;

        for (int r = 0; r < rows; ++r) {
            if (leftToRight) {
                for (int c = 0; c < cols; c += 2) {
                    result.push_back(grid[r][c]);
                }
            } else {
                for (int c = cols - 1; c >= 0; c -= 2) {
                    result.push_back(grid[r][c]);
                }
            }
            leftToRight = !leftToRight;
        }

        return result;          
    }
};
