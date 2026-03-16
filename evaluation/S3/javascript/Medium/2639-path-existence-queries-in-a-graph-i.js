// Source: https://leetcode.com/problems/path-existence-queries-in-a-graph-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.
//
// You are also given an integer array nums of length n sorted in non-decreasing order, and an integer maxDiff.
//
// An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).
//
// You are also given a 2D integer array queries. For each queries[i] = [ui, vi], determine whether there exists a path between nodes ui and vi.
//
// Return a boolean array answer, where answer[i] is true if there exists a path between ui and vi in the ith query and false otherwise.
//
// Example:
// Input: n = 2, nums = [1,3], maxDiff = 1, queries = [[0,0],[0,1]]
//
// Output: [true,false]
//
// Explanation:
//
//
// 	Query [0,0]: Node 0 has a trivial path to itself.
// 	Query [0,1]: There is no edge between Node 0 and Node 1 because |nums[0] - nums[1]| = |1 - 3| = 2, which is greater than maxDiff.
// 	Thus, the final answer after processing all the queries is [true, false].
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	0 <= nums[i] <= 105
// 	nums is sorted in non-decreasing order.
// 	0 <= maxDiff <= 105
// 	1 <= queries.length <= 105
// 	queries[i] == [ui, vi]
// 	0 <= ui, vi < n
//
// Helpful references (internal KB):
// - Minimum spanning tree - Kruskal with Disjoint Set Union (graph, ds, mst-kruskal, union-find)
//   • When to use: Use when you need to find a minimum spanning tree in a graph, especially when the graph is sparse or the number of edges is not excessively large compared to vertices.
//   • Idea: Sorts all graph edges by weight and iteratively adds the cheapest edge that connects two previously disconnected components using a Disjoint Set Union (DSU) data structure. This process builds an MST with O(M log M) or O(M log N) time complexity.
//   • Invariants: After processing k edges, the chosen edges form a forest where each tree is a component of the MST.; Any edge not yet processed has a weight greater than or equal to all processed edges.
//   • Tips: Sort edges by weight in non-decreasing order.; Initialize DSU such that each vertex is in its own set.
//   • Pitfalls: Forgetting to sort edges, leading to an incorrect MST.; Inefficient DSU implementation without path compression or union by rank/size.
// - Finding Bridges Online (graph, ds, union-find, counting)
//   • When to use: Use when edges are added one by one to an initially empty graph and you need to efficiently track the number of bridges or 2-edge-connected components after each addition.
//   • Idea: This algorithm dynamically maintains the number of bridges in an undirected graph as edges are added incrementally. It leverages a Disjoint Set Union (DSU) data structure to achieve an amortized time complexity of O((N+M) log N).
//   • Invariants: Each DSU set represents a 2-edge-connected component or a collection of such components connected by bridges.; The total count of bridges accurately reflects edges whose removal increases connected components.
//   • Tips: Understand the properties of 2-edge-connected components and how they relate to bridges.; Carefully manage DSU operations, including path compression and union by rank/size, for optimal performance.
//   • Pitfalls: Incorrectly updating the bridge count after an edge addition, especially when cycles are formed.; Inefficient DSU operations leading to a higher than expected time complexity.
// - Range Minimum Query (array, ds, union-find)
//   • When to use: Use when range minimum queries are needed on an array where elements can be dynamically removed or merged, and Union-Find is employed to manage the active state or connectivity of indices.
//   • Idea: Union-Find can be adapted to assist in range minimum queries, particularly when elements are dynamically removed or merged. It helps maintain connectivity of active elements or segments, allowing efficient traversal to find the minimum among available items, often with near-constant amortized time per Union-Find operation.
//   • Invariants: The `find` operation correctly returns the canonical representative for any element `i`.; Each set in the Union-Find structure maintains a property (e.g., minimum value, next available index) relevant to its merged elements.
//   • Tips: Utilize path compression and union by rank/size for optimal Union-Find performance.; Store relevant properties (e.g., minimum value, next available index) within the representative of each set.
//   • Pitfalls: Union-Find alone does not directly provide range minimums; it typically manages connectivity or availability.; Naive iteration through active elements found by Union-Find can be too slow for large ranges.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[]} nums
 * @param {number} maxDiff
 * @param {number[][]} queries
 * @return {boolean[]}
 */
var pathExistenceQueries = function(n, nums, maxDiff, queries) {
    const results = [];
    for (const [u, v] of queries) {
        results.push(Math.abs(nums[u] - nums[v]) <= maxDiff);
    }
    return results;
};
