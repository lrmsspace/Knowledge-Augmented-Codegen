// Source: https://leetcode.com/problems/count-artifacts-that-can-be-extracted/   |   Difficulty: Medium
//
// Problem Description:
// There is an n x n 0-indexed grid with some artifacts buried in it. You are given the integer n and a 0-indexed 2D integer array artifacts describing the positions of the rectangular artifacts where artifacts[i] = [r1i, c1i, r2i, c2i] denotes that the ith artifact is buried in the subgrid where:
//
//
// 	(r1i, c1i) is the coordinate of the top-left cell of the ith artifact and
// 	(r2i, c2i) is the coordinate of the bottom-right cell of the ith artifact.
//
//
// You will excavate some cells of the grid and remove all the mud from them. If the cell has a part of an artifact buried underneath, it will be uncovered. If all the parts of an artifact are uncovered, you can extract it.
//
// Given a 0-indexed 2D integer array dig where dig[i] = [ri, ci] indicates that you will excavate the cell (ri, ci), return the number of artifacts that you can extract.
//
// The test cases are generated such that:
//
//
// 	No two artifacts overlap.
// 	Each artifact only covers at most 4 cells.
// 	The entries of dig are unique.
//
// Example:
// Input: n = 2, artifacts = [[0,0,0,0],[0,1,1,1]], dig = [[0,0],[0,1]]
// Output: 1
// Explanation: 
// The different colors represent different artifacts. Excavated cells are labeled with a 'D' in the grid.
// There is 1 artifact that can be extracted, namely the red artifact.
// The blue artifact has one part in cell (1,1) which remains uncovered, so we cannot extract it.
// Thus, we return 1.
//
// Constraints:
// 1 <= n <= 1000
// 	1 <= artifacts.length, dig.length <= min(n2, 105)
// 	artifacts[i].length == 4
// 	dig[i].length == 2
// 	0 <= r1i, c1i, r2i, c2i, ri, ci <= n - 1
// 	r1i <= r2i
// 	c1i <= c2i
// 	No two artifacts will overlap.
// 	The number of cells covered by an artifact is at most 4.
// 	The entries of dig are unique.
//
// Helpful references (internal KB):
// - Placing Bishops on a Chessboard (array, counting, dp-2d)
//   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
//   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
//   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
//   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
//   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
// - Search for a pair of intersecting segments (geometry, enumeration, sweep-line)
//   • When to use: When needing to efficiently detect if any two line segments among a given set intersect, or to find one such intersecting pair.
//   • Idea: This algorithm efficiently determines if any two line segments in a given set intersect by processing events along a sweep line, typically achieving O(N log N) time complexity.
//   • Invariants: All segments fully to the left of the sweep line have been processed and do not intersect each other.; The active set contains all segments currently intersecting the sweep line, ordered by their y-coordinate.
//   • Tips: Represent segments by their endpoints as event points, sorted by x-coordinate.; Use a balanced binary search tree (or similar structure) to maintain active segments ordered by their y-coordinate at the sweep line.
//   • Pitfalls: Floating point precision issues can lead to incorrect intersection detection or ordering.; Degenerate cases like collinear segments or multiple segments intersecting at a single point.
// - Directed Graphs (graph, matrix, dfs)
//   • When to use: Use when needing to determine reachability between all pairs of vertices in a directed graph, especially for small or dense graphs where O(V*(V+E)) time is acceptable.
//   • Idea: This approach determines all-pairs reachability in a directed graph by performing a Depth-First Search starting from each vertex. It has a time complexity of O(V*(V+E)) and a space complexity of O(V^2).
//   • Invariants: For any vertex u, after its dedicated DFS completes, TC[u][v] is true for all v reachable from u.; The transitive closure matrix TC accurately reflects all-pairs reachability in the original graph.
//   • Tips: Initialize a boolean matrix to store reachability results.; For each vertex, perform a full DFS to mark all nodes reachable from it.
//   • Pitfalls: High time complexity O(V*(V+E)) makes it unsuitable for large sparse graphs.; High space complexity O(V^2) can be prohibitive for graphs with many vertices.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int digArtifacts(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig) {
        unordered_set<string> dug;
        for (const auto& d : dig) {
            dug.insert(to_string(d[0]) + "," + to_string(d[1]));
        }

        int count = 0;
        for (const auto& artifact : artifacts) {
            bool canExtract = true;
            for (int r = artifact[0]; r <= artifact[2]; ++r) {
                for (int c = artifact[1]; c <= artifact[3]; ++c) {
                    if (dug.find(to_string(r) + "," + to_string(c)) == dug.end()) {
                        canExtract = false;
                        break;
                    }
                }
                if (!canExtract) break;
            }
            if (canExtract) ++count;
        }

        return count;           
    }
};
