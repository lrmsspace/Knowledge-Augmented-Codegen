// Source: https://leetcode.com/problems/select-cells-in-grid-with-maximum-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D matrix grid consisting of positive integers.
//
// You have to select one or more cells from the matrix such that the following conditions are satisfied:
//
//
// 	No two selected cells are in the same row of the matrix.
// 	The values in the set of selected cells are unique.
//
//
// Your score will be the sum of the values of the selected cells.
//
// Return the maximum score you can achieve.
//
// Example:
// Input: grid = [[1,2,3],[4,3,2],[1,1,1]]
//
// Output: 8
//
// Explanation:
//
//
//
// We can select the cells with values 1, 3, and 4 that are colored above.
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 10
// 	1 <= grid[i][j] <= 100
//
// Helpful references (internal KB):
// - Finding a negative cycle in the graph (graph, array, bellman-ford)
//   • When to use: Use when a graph may contain negative edge weights and you need to find the shortest paths from a single source, or specifically to detect and identify negative cycles.
//   • Idea: The Bellman-Ford algorithm computes single-source shortest paths in a weighted graph, even with negative edge weights, and can detect negative cycles. It has a time complexity of O(VE).
//   • Invariants: After k iterations, dist[v] is the shortest path from the source to v using at most k edges.; If no negative cycle is reachable, dist[v] will be the true shortest path distance after V-1 iterations.
//   • Tips: Perform V-1 iterations for shortest path calculation, then one more for cycle detection.; A negative cycle exists if any distance can still be reduced in the V-th iteration.
//   • Pitfalls: Inefficient for graphs with only non-negative weights compared to Dijkstra's.; Does not directly work for undirected graphs with negative edges.
// - Minimum-cost flow - Successive shortest path algorithm (graph, array, greedy, dijkstra, bellman-ford)
//   • When to use: This algorithm finds a minimum-cost flow of a given amount from a source to a sink in a flow network. It is suitable when both flow capacity and edge costs are present.
//   • Idea: The successive shortest path algorithm iteratively finds augmenting paths with minimum cost in a residual graph, using shortest path algorithms like Bellman-Ford or Dijkstra with potentials, until the desired flow is achieved. Its complexity depends on the shortest path algorithm used and the number of augmentations.
//   • Invariants: The total flow pushed from source to sink never exceeds the sum of capacities of edges leaving the source.; For any edge (u, v) with flow f_uv, 0 <= f_uv <= capacity_uv.
//   • Tips: Use potentials with Dijkstra for non-negative edge costs in the residual graph.; Bellman-Ford is necessary if initial edge costs can be negative or if potentials are not used.
//   • Pitfalls: Incorrectly updating potentials can lead to wrong shortest paths.; Forgetting to add reverse edges with negative costs in the residual graph.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxScore(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];
    int maxMask = 1 << rows;
    int *dp = (int*)calloc(maxMask, sizeof(int));
    for (int c = 0; c < cols; ++c) {
        int *newDp = (int*)calloc(maxMask, sizeof(int));
        for (int mask = 0; mask < maxMask; ++mask) {
            newDp[mask] = dp[mask];
        }
        for (int mask = 0; mask < maxMask; ++mask) {
            for (int r = 0; r < rows; ++r) {
                if ((mask & (1 << r)) == 0) { /* row r not selected yet */
                    int newMask = mask | (1 << r);
                    int newScore = dp[mask] + grid[r][c];
                    if (newScore > newDp[newMask]) {
                        newDp[newMask] = newScore;
                    }
                }
            }
        }
        free(dp);
        dp = newDp;
    }
    int maxScore = 0;
    for (int mask = 0; mask < maxMask; ++mask) {
        if (dp[mask] > maxScore) {
            maxScore = dp[mask];
        }
    }
    free(dp);
    return maxScore;        
}
