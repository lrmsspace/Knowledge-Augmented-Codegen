// Source: https://leetcode.com/problems/regions-cut-by-slashes/   |   Difficulty: Medium
//
// Problem Description:
// An n x n grid is composed of 1 x 1 squares where each 1 x 1 square consists of a '/', '\', or blank space ' '. These characters divide the square into contiguous regions.
//
// Given the grid grid represented as a string array, return the number of regions.
//
// Note that backslash characters are escaped, so a '\' is represented as '\\'.
//
// Example:
// Input: grid = [" /","/ "]
// Output: 2
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 30
// 	grid[i][j] is either '/', '\', or ' '.
//
// Helpful references (internal KB):
// - Placing Bishops on a Chessboard (array, counting, dp-2d)
//   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
//   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
//   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
//   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
//   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size();
        int size = n * 3; // Each cell is divided into 3 parts
        vector<vector<int>> graph(size, vector<int>(size, 0));

        // Build the graph based on the slashes
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int root = (i * n + j) * 3;
                if (grid[i][j] == '/') {
                    graph[root][root + 1] = graph[root + 1][root] = 1;
                    graph[root + 1][root + 2] = graph[root + 2][root + 1] = 1;
                } else if (grid[i][j] == '\\') {
                    graph[root][root + 2] = graph[root + 2][root] = 1;
                    graph[root + 1][root + 2] = graph[root + 2][root + 1] = 1;
                } else {
                    graph[root][root + 1] = graph[root + 1][root] = 1;
                    graph[root][root + 2] = graph[root + 2][root] = 1;
                    graph[root + 1][root + 2] = graph[root + 2][root + 1] = 1;
                }
            }
        }

        // Count connected components using DFS
        vector<bool> visited(size, false);
        int regions = 0;

        function<void(int)> dfs = [&](int node) {
            visited[node] = true;
            for (int neighbor = 0; neighbor < size; ++neighbor) {
                if (graph[node][neighbor] && !visited[neighbor]) {
                    dfs(neighbor);
                }
            }
        };

        for (int i = 0; i < size; ++i) {
            if (!visited[i]) {
                dfs(i);
                ++regions;
            }
        }

        return regions;         
    }
};
