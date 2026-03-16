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
// - Hungarian algorithm for solving the assignment problem (matrix, graph, array, greedy, bfs, enumeration)
//   • When to use: Use when finding a minimum cost perfect matching in a bipartite graph, typically represented as an N x N cost matrix, where each row must be assigned to exactly one column.
//   • Idea: The Hungarian algorithm finds a minimum weight perfect matching in a bipartite graph, solving the assignment problem for an N x N cost matrix. It iteratively finds augmenting paths in an equality graph and adjusts potentials, achieving O(N^3) time complexity.
//   • Invariants: For all i, j, u[i] + v[j] <= A[i][j] (potential condition).; The current matching is always valid (each row/column used at most once).
//   • Tips: Understand the concept of potentials and their role in maintaining the equality graph.; The algorithm can be adapted for maximum profit problems by negating costs.
//   • Pitfalls: Incorrectly updating potentials can lead to non-optimal solutions or infinite loops.; Handling non-square matrices requires careful padding with dummy values.
// - Solving assignment problem using min-cost-flow (graph, dijkstra, bellman-ford)
//   • When to use: Use when finding a one-to-one assignment between two sets of entities, such as workers to tasks, to minimize the total cost. It's suitable for problems modelable as min-cost max-flow in a bipartite graph.
//   • Idea: This technique models the assignment problem as a minimum cost maximum flow problem on a specially constructed bipartite graph. It finds a perfect matching with the lowest total cost, typically with a polynomial time complexity depending on the shortest path algorithm used.
//   • Invariants: Flow conservation holds for all intermediate nodes in the network.; The flow on any edge never exceeds its defined capacity.
//   • Tips: Construct a bipartite graph with a source and sink nodes.; Set capacities to 1 for all assignment-related edges to ensure one-to-one mapping.
//   • Pitfalls: Incorrectly modeling capacities or costs on graph edges can lead to wrong solutions.; Forgetting to ensure a perfect matching (flow value equals N) is found for a complete assignment.
// - Minimum-cost flow - Successive shortest path algorithm (graph, array, number, greedy, dijkstra, bellman-ford)
//   • When to use: When you need to find a flow of a certain amount (or maximum possible flow) through a network while minimizing the total cost associated with sending flow along edges. It is suitable for problems involving resource allocation with varying costs.
//   • Idea: The successive shortest path algorithm finds a minimum-cost flow by repeatedly finding a shortest augmenting path in the residual graph and pushing flow along it. Its complexity depends on the shortest path algorithm used (Bellman-Ford for general costs, Dijkstra with potentials for non-negative residual costs).
//   • Invariants: At the start of each iteration, the current flow is a valid flow from source to sink.; The residual graph correctly represents remaining capacities and reverse edges for the current flow.
//   • Tips: Use potentials (reduced costs) with Dijkstra to efficiently handle non-negative edge costs in the residual graph.; Initialize potentials to zero and update them after each shortest path computation.
//   • Pitfalls: Incorrectly updating residual capacities or reverse edge costs can lead to wrong results.; Failing to use potentials with Dijkstra can lead to incorrect shortest paths in graphs with negative edges.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} grid
 * @return {number}
 */
var maxScore = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const dp = Array(m).fill().map(() => Array(n).fill(-Infinity));
    dp[0][0] = grid[0][0];
    
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (i > 0) {
                dp[i][j] = Math.max(dp[i][j], dp[i - 1][j] + grid[i][j]);
            }
            if (j > 0) {
                dp[i][j] = Math.max(dp[i][j], dp[i][j - 1] + grid[i][j]);
            }
        }
    }
    
    return dp[m - 1][n - 1];
};
