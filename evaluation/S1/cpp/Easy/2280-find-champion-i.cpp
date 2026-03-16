// Source: https://leetcode.com/problems/find-champion-i/   |   Difficulty: Easy
//
// Problem Description:
// There are n teams numbered from 0 to n - 1 in a tournament.
//
// Given a 0-indexed 2D boolean matrix grid of size n * n. For all i, j that 0 <= i, j <= n - 1 and i != j team i is stronger than team j if grid[i][j] == 1, otherwise, team j is stronger than team i.
//
// Team a will be the champion of the tournament if there is no team b that is stronger than team a.
//
// Return the team that will be the champion of the tournament.
//
// Example:
// Input: grid = [[0,1],[0,0]]
// Output: 0
// Explanation: There are two teams in this tournament.
// grid[0][1] == 1 means that team 0 is stronger than team 1. So team 0 will be the champion.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	2 <= n <= 100
// 	grid[i][j] is either 0 or 1.
// 	For all i grid[i][i] is 0.
// 	For all i, j that i != j, grid[i][j] != grid[j][i].
// 	The input is generated such that if team a is stronger than team b and team b is stronger than team c, then team a is stronger than team c.
//
// Helpful references (internal KB):
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
// - Strongly connected components and the condensation graph (graph, enumeration)
//   • When to use: When you need to identify maximal subgraphs where all vertices are mutually reachable, or to simplify a directed graph into a Directed Acyclic Graph (DAG) of components for further processing.
//   • Idea: This concept defines SCCs as maximal vertex subsets in a directed graph where all pairs are mutually reachable. It also introduces the condensation graph, which represents SCCs as nodes and forms a DAG, typically found in O(V+E) time.
//   • Invariants: Every vertex belongs to exactly one strongly connected component.; Within any SCC, a path exists from any vertex u to any other vertex v, and vice-versa.
//   • Tips: Understand that SCCs partition the graph's vertices.; The condensation graph is always a Directed Acyclic Graph (DAG).
//   • Pitfalls: Confusing SCCs with simple cycles or connected components in undirected graphs.; Incorrectly assuming the condensation graph has cycles.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int findChampion(vector<vector<int>>& grid) {
        int n = grid.size();
        for (int i = 0; i < n; ++i) {
            bool isChampion = true;
            for (int j = 0; j < n; ++j) {
                if (i != j && grid[j][i] == 1) {
                    isChampion = false;
                    break;
                }
            }
            if (isChampion) {
                return i;
            }
        }
        return -1;  // Should not reach here as per problem constraints         
    }
};
