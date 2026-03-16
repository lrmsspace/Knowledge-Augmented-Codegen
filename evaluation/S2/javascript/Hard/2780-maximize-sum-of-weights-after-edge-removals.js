// Source: https://leetcode.com/problems/maximize-sum-of-weights-after-edge-removals/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi in the tree.
//
// Your task is to remove zero or more edges such that:
//
//
// 	Each node has an edge with at most k other nodes, where k is given.
// 	The sum of the weights of the remaining edges is maximized.
//
//
// Return the maximum possible sum of weights for the remaining edges after making the necessary removals.
//
// Example:
// Input: edges = [[0,1,4],[0,2,2],[2,3,12],[2,4,6]], k = 2
//
// Output: 22
//
// Explanation:
//
//
//
//
// 	Node 2 has edges with 3 other nodes. We remove the edge [0, 2, 2], ensuring that no node has edges with more than k = 2 nodes.
// 	The sum of weights is 22, and we can't achieve a greater sum. Thus, the answer is 22.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= k <= n - 1
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= edges[i][0] <= n - 1
// 	0 <= edges[i][1] <= n - 1
// 	1 <= edges[i][2] <= 106
// 	The input is generated such that edges form a valid tree.
//
// Helpful references (internal KB):
// - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
//   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
//   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
//   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
//   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
//   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} edges
 * @param {number} k
 * @return {number}
 */
var maximizeSumOfWeights = function(edges, k) {
    const n = edges.length + 1;
    const graph = new Array(n).fill(0).map(() => []);
    for (const [u, v, w] of edges) {
        graph[u].push([v, w]);
        graph[v].push([u, w]);
    }
    let totalWeight = 0;
    for (const [u, v, w] of edges) {
        totalWeight += w;
    }
    const degree = new Array(n).fill(0);
    for (const [u, v] of edges) {
        degree[u]++;
        degree[v]++;
    }
    const pq = [];
    for (let i = 0; i < n; i++) {
        if (degree[i] > k) {
            pq.push(i);
        }
    }
    while (pq.length) {
        const node = pq.pop();
        if (degree[node] <= k) {
            continue;
        }
        let maxWeight = -1, maxNeighbor = -1;
        for (const [neighbor, weight] of graph[node]) {
            if (weight > maxWeight) {
                maxWeight = weight;
                maxNeighbor = neighbor;
            }
        }
        totalWeight -= maxWeight;
        degree[node]--;
        degree[maxNeighbor]--;
        if (degree[maxNeighbor] > k) {
            pq.push(maxNeighbor);
        }
    }
    return totalWeight;
};
