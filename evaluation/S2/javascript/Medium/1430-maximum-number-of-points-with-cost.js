// Source: https://leetcode.com/problems/maximum-number-of-points-with-cost/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix points (0-indexed). Starting with 0 points, you want to maximize the number of points you can get from the matrix.
//
// To gain points, you must pick one cell in each row. Picking the cell at coordinates (r, c) will add points[r][c] to your score.
//
// However, you will lose points if you pick a cell too far from the cell that you picked in the previous row. For every two adjacent rows r and r + 1 (where 0 <= r < m - 1), picking cells at coordinates (r, c1) and (r + 1, c2) will subtract abs(c1 - c2) from your score.
//
// Return the maximum number of points you can achieve.
//
// abs(x) is defined as:
//
//
// 	x for x >= 0.
// 	-x for x < 0.
//
// Example:
// Input: points = [[1,2,3],[1,5,1],[3,1,1]]
// Output: 9
// Explanation:
// The blue cells denote the optimal cells to pick, which have coordinates (0, 2), (1, 1), and (2, 0).
// You add 3 + 5 + 3 = 11 to your score.
// However, you must subtract abs(2 - 1) + abs(1 - 0) = 2 from your score.
// Your final score is 11 - 2 = 9.
//
// Constraints:
// m == points.length
// 	n == points[r].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	0 <= points[r][c] <= 105
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} points
 * @return {number}
 */
var maxPoints = function(points) {
     const m = points.length;
    const n = points[0].length;
    let dp = new Array(n).fill(0);
    for (let c = 0; c < n; c++) {
        dp[c] = points[0][c];
    }
    for (let r = 1; r < m; r++) {
        const newDp = new Array(n).fill(0);
        let maxLeft = new Array(n).fill(0);
        let maxRight = new Array(n).fill(0);
        maxLeft[0] = dp[0];
        for (let c = 1; c < n; c++) {
            maxLeft[c] = Math.max(maxLeft[c - 1] - 1, dp[c]);
        }
        maxRight[n - 1] = dp[n - 1];
        for (let c = n - 2; c >= 0; c--) {
            maxRight[c] = Math.max(maxRight[c + 1] - 1, dp[c]);
        }
        for (let c = 0; c < n; c++) {
            newDp[c] = points[r][c] + Math.max(maxLeft[c], maxRight[c]);
        }
        dp = newDp;
    }
    return Math.max(...dp);
};
