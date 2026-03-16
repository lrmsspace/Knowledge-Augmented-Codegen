// Source: https://leetcode.com/problems/minimum-cost-to-reach-every-position/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array cost of size n. You are currently at position n (at the end of the line) in a line of n + 1 people (numbered from 0 to n).
//
// You wish to move forward in the line, but each person in front of you charges a specific amount to swap places. The cost to swap with person i is given by cost[i].
//
// You are allowed to swap places with people as follows:
//
//
// 	If they are in front of you, you must pay them cost[i] to swap with them.
// 	If they are behind you, they can swap with you for free.
//
//
// Return an array answer of size n, where answer[i] is the minimum total cost to reach each position i in the line.
//
// Example:
// Input: cost = [5,3,4,1,3,2]
//
// Output: [5,3,3,1,1,1]
//
// Explanation:
//
// We can get to each position in the following way:
//
//
// 	i = 0. We can swap with person 0 for a cost of 5.
// 	i = 1. We can swap with person 1 for a cost of 3.
// 	i = 2. We can swap with person 1 for a cost of 3, then swap with person 2 for free.
// 	i = 3. We can swap with person 3 for a cost of 1.
// 	i = 4. We can swap with person 3 for a cost of 1, then swap with person 4 for free.
// 	i = 5. We can swap with person 3 for a cost of 1, then swap with person 5 for free.
//
// Constraints:
// 1 <= n == cost.length <= 100
// 	1 <= cost[i] <= 100
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Introduction to Dynamic Programming (array, dp-1d)
//   • When to use: When a problem can be broken down into smaller, overlapping subproblems and an optimal solution to the larger problem can be constructed from optimal solutions to its subproblems. It's suitable for optimizing recursive solutions with repeated computations.
//   • Idea: Dynamic Programming (DP) solves complex problems by breaking them into simpler overlapping subproblems and storing the results to avoid redundant computations. It typically achieves polynomial time complexity, often O(N) or O(N^2) for 1D DP, by trading space for time.
//   • Invariants: dp[i] stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been correctly computed before dp[i] is calculated.
//   • Tips: Clearly define the DP state and its meaning.; Identify the base cases for the recurrence relation.
//   • Pitfalls: Incorrectly defining the DP state or recurrence relation.; Missing or incorrect base cases leading to infinite recursion or wrong results.
// - Shortest Paths (array, graph, dp-1d)
//   • When to use: To find the path with the minimum total weight or cost between two vertices, or from a single source to all other reachable vertices, in an edge-weighted graph.
//   • Idea: Shortest path algorithms determine the path with the least cumulative weight between nodes in a graph. This often involves a dynamic programming approach, iteratively updating minimum distances to achieve an optimal O(V*E) or O(E log V) complexity.
//   • Invariants: distTo[v] always stores the minimum path length from the source to v discovered so far.; For any edge u -> v, if distTo[u] is final, then distTo[v] will eventually be min(distTo[v], distTo[u] + weight(u,v)).
//   • Tips: Initialize the source distance to 0 and all other distances to infinity.; Use a `distTo` array to store the current shortest distances from the source.
//   • Pitfalls: Failing to detect or handle negative cycles, which can lead to infinite loops or incorrect results.; Incorrectly initializing distances or edge relaxation logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} cost
 * @return {number[]}
 */
var minCosts = function(cost) {
    const n = cost.length;
    const dp = new Array(n).fill(0); // Initialize a DP array to store the minimum cost to reach each position
    dp[0] = cost[0]; // The cost to reach position 0 is simply the cost of swapping with person 0
    for (let i = 1; i < n; i++) {
        dp[i] = Math.min(dp[i - 1] + cost[i], cost[i]); // The cost to reach position i is either swapping with person i directly or swapping with the previous position and then swapping with person i
    }
    return dp; // Return the DP array containing the minimum costs to reach each position
};
