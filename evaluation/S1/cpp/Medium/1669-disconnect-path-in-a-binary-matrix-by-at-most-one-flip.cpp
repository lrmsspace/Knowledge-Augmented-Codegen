// Source: https://leetcode.com/problems/disconnect-path-in-a-binary-matrix-by-at-most-one-flip/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed m x n binary matrix grid. You can move from a cell (row, col) to any of the cells (row + 1, col) or (row, col + 1) that has the value 1. The matrix is disconnected if there is no path from (0, 0) to (m - 1, n - 1).
//
// You can flip the value of at most one (possibly none) cell. You cannot flip the cells (0, 0) and (m - 1, n - 1).
//
// Return true if it is possible to make the matrix disconnect or false otherwise.
//
// Note that flipping a cell changes its value from 0 to 1 or from 1 to 0.
//
// Example:
// Input: grid = [[1,1,1],[1,0,0],[1,1,1]]
// Output: true
// Explanation: We can change the cell shown in the diagram above. There is no path from (0, 0) to (2, 2) in the resulting grid.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	grid[i][j] is either 0 or 1.
// 	grid[0][0] == grid[m - 1][n - 1] == 1
//
// Helpful references (internal KB):
// - Maximum flow - Dinic's algorithm (graph, bfs, dfs)
//   • When to use: Use Dinic's algorithm to find the maximum flow from a source to a sink in a flow network. It is efficient for dense graphs and particularly optimized for unit capacity networks.
//   • Idea: Dinic's algorithm computes the maximum flow by repeatedly constructing a layered network using BFS and then finding a blocking flow in this layered network using DFS. It offers a general time complexity of O(V^2 * E) and O(E * sqrt(V)) for unit capacity networks.
//   • Invariants: The flow on any edge (u, v) never exceeds its original capacity.; For any vertex v (excluding source and sink), the sum of flow into v equals the sum of flow out of v.
//   • Tips: Use BFS to construct the layered graph, assigning levels to nodes from the source.; Employ DFS to find augmenting paths within the layered graph, only traversing edges to higher levels.
//   • Pitfalls: Forgetting to update residual capacities for reverse edges, which can prevent finding valid augmenting paths.; Incorrectly constructing the layered graph or level assignments during the BFS phase.
// - Edge connectivity / Vertex connectivity (graph, enumeration)
//   • When to use: Used to quantify a graph's resilience by finding the minimum number of edges or vertices whose removal disconnects it, or separates a specific pair of nodes.
//   • Idea: Edge connectivity is the minimum edges to disconnect a graph, while vertex connectivity is for vertices. Both are often computed using max-flow min-cut theorems, typically in polynomial time.
//   • Invariants: The flow through any edge in the network does not exceed its capacity.; For any intermediate vertex (not source or sink), the total incoming flow equals the total outgoing flow.
//   • Tips: Edge connectivity between two specific vertices can be found using a max-flow min-cut algorithm.; To find global edge connectivity, iterate over all pairs of vertices or use specialized algorithms.
//   • Pitfalls: Confusing edge connectivity (edges) with vertex connectivity (vertices) requirements.; Incorrectly applying max-flow for global connectivity without considering all relevant source-sink pairs.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool isPossibleToCutPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp1(m, vector<int>(n, 0));
        vector<vector<int>> dp2(m, vector<int>(n, 0));

        // Forward DP to count paths from (0,0) to each cell
        dp1[0][0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) continue;
                if (i > 0) dp1[i][j] += dp1[i-1][j];
                if (j > 0) dp1[i][j] += dp1[i][j-1];
            }
        }

        // Backward DP to count paths from each cell to (m-1,n-1)
        dp2[m-1][n-1] = 1;
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (grid[i][j] == 0) continue;
                if (i < m - 1) dp2[i][j] += dp2[i+1][j];
                if (j < n - 1) dp2[i][j] += dp2[i][j+1];
            }
        }

        int totalPaths = dp1[m-1][n-1];
        // Check for any cell that is on all paths
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i == 0 && j == 0) || (i == m - 1 && j == n - 1)) continue;
                if (grid[i][j] == 1 && dp1[i][j] * dp2[i][j] == totalPaths && totalPaths > 0) {
                    return true;
                }
            }
        }

        return false;           
    }
};
