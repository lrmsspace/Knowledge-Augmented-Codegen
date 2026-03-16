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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean isPossibleToCutPath(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        // If the grid is too small, we cannot disconnect the path by flipping one cell
        if (m + n - 1 <= 2) {
            return false;
        }

        // Create a graph with vertex splitting to handle vertex capacities
        int totalVertices = m * n * 2;
        Dinic dinic = new Dinic(totalVertices);

        // Build the graph
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int inVertex = (i * n + j) * 2;
                    int outVertex = inVertex + 1;

                    // Connect in-vertex to out-vertex with capacity 1
                    dinic.addEdge(inVertex, outVertex, 1);

                    // Connect to right neighbor
                    if (j + 1 < n && grid[i][j + 1] == 1) {
                        int rightInVertex = (i * n + (j + 1)) * 2;
                        dinic.addEdge(outVertex, rightInVertex, Integer.MAX_VALUE);
                    }

                    // Connect to bottom neighbor
                    if (i + 1 < m && grid[i + 1][j] == 1) {
                        int downInVertex = ((i + 1) * n + j) * 2;
                        dinic.addEdge(outVertex, downInVertex, Integer.MAX_VALUE);
                    }
                }
            }
        }

        int source = 0; // (0,0) in-vertex
        int sink = (m * n - 1) * 2 + 1; // (m-1,n-1) out-vertex

        // Calculate max flow which corresponds to min cut
        int maxFlow = dinic.maxFlow(source, sink);

        // If the min cut is less than or equal to 1, we can disconnect the path by flipping one cell
        return maxFlow <= 1;            
    }
}
