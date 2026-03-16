// Source: https://leetcode.com/problems/trapping-rain-water-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
//
// Example:
// Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
// Output: 4
// Explanation: After the rain, water is trapped between the blocks.
// We have two small ponds 1 and 3 units trapped.
// The total volume of water trapped is 4.
//
// Constraints:
// m == heightMap.length
// 	n == heightMap[i].length
// 	1 <= m, n <= 200
// 	0 <= heightMap[i][j] <= 2 * 104
//
// Helpful references (internal KB):
// - Maximum flow - Push-relabel algorithm (graph, number, simulation)
//   • When to use: Use when computing the maximum flow in a network, especially for dense graphs where its O(V^2 E) complexity can be competitive. It's an alternative to augmenting path algorithms.
//   • Idea: The Push-relabel algorithm computes maximum flow by maintaining a preflow and a height function, iteratively pushing excess flow from vertices and relabeling them until a valid flow is achieved. It typically runs in O(V^2 E) time.
//   • Invariants: For any edge (u, v) in the residual graph with positive capacity, h(u) <= h(v) + 1.; Excess flow at the source (s) is always non-negative, and at the sink (t) is always non-positive.
//   • Tips: Initialize the graph with a valid preflow and height function.; Prioritize pushing excess from vertices with the highest labels.
//   • Pitfalls: Incorrectly updating residual capacities after a push operation.; Violating the height function validity condition (h(u) <= h(v) + 1).
// - Maximum flow - Push-relabel algorithm (graph, number, simulation)
//   • When to use: Use when finding the maximum flow in a network, particularly for dense graphs or when the Ford-Fulkerson method is too slow due to many augmenting paths.
//   • Idea: The Push-relabel algorithm computes maximum flow by maintaining a preflow and a height function, iteratively pushing excess flow from higher to lower nodes and relabeling nodes until all excess is pushed to the sink. It is a highly efficient polynomial-time algorithm for various graph structures.
//   • Invariants: For any vertex v (not source or sink), the total incoming flow minus total outgoing flow is non-negative (excess flow).; For any edge (u, v) in the residual graph with positive capacity, the height of u is at most h(v) + 1.
//   • Tips: Understand the concepts of preflow and excess flow.; Correctly implement push and relabel operations.
//   • Pitfalls: Incorrectly updating residual capacities after a push.; Failing to maintain the height function property (h(u) <= h(v) + 1).
// - Maximum flow - Push-relabel algorithm (graph, queue, simulation)
//   • When to use: Used for finding the maximum flow in a flow network. It is particularly efficient for dense graphs or when the Ford-Fulkerson method is too slow due to many augmenting paths.
//   • Idea: The Push-relabel algorithm computes maximum flow by maintaining a preflow and a height function, iteratively pushing excess flow from higher to lower nodes and relabeling nodes when flow cannot be pushed. It typically achieves a time complexity of O(V^2 * E) or O(V^3) with specific implementations.
//   • Invariants: For any edge (u, v) with positive residual capacity, h(u) <= h(v) + 1.; The source s always has h(s) = |V| and the sink t always has h(t) = 0.
//   • Tips: Initialize preflow by saturating edges from the source.; Initialize source height to |V| and others to 0.
//   • Pitfalls: Incorrectly handling residual capacities.; Not maintaining the height invariant during pushes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int trapRainWater(int** heightMap, int heightMapSize, int* heightMapColSize) {
    // Implement a priority queue (min-heap) to store the boundary cells of the height map
    // Initialize the priority queue with all the boundary cells and mark them as visited
    // While the priority queue is not empty, pop the cell with the lowest height
    // For each of its unvisited neighbors, calculate the trapped water and update the neighbor's height if necessary, then push it into the priority queue
    // Keep track of the total trapped water and return it at the end
    return 0; // Placeholder return value
}
