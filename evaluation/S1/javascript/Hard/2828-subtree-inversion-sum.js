// Source: https://leetcode.com/problems/subtree-inversion-sum/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0, with n nodes numbered from 0 to n - 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates an edge between nodes ui and vi.
//
// You are also given an integer array nums of length n, where nums[i] represents the value at node i, and an integer k.
//
// You may perform inversion operations on a subset of nodes subject to the following rules:
//
//
// 	
// 	Subtree Inversion Operation:
//
// 	
// 		
// 		When you invert a node, every value in the subtree rooted at that node is multiplied by -1.
// 		
// 	
// 	
// 	
// 	Distance Constraint on Inversions:
//
// 	
// 		
// 		You may only invert a node if it is "sufficiently far" from any other inverted node.
// 		
// 		
// 		Specifically, if you invert two nodes a and b such that one is an ancestor of the other (i.e., if LCA(a, b) = a or LCA(a, b) = b), then the distance (the number of edges on the unique path between them) must be at least k.
// 		
// 	
// 	
//
//
// Return the maximum possible sum of the tree's node values after applying inversion operations.
//
// Example:
// Input: edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]], nums = [4,-8,-6,3,7,-2,5], k = 2
//
// Output: 27
//
// Explanation:
//
//
//
//
// 	Apply inversion operations at nodes 0, 3, 4 and 6.
// 	The final nums array is [-4, 8, 6, 3, 7, 2, 5], and the total sum is 27.
//
// Constraints:
// 2 <= n <= 5 * 104
// 	edges.length == n - 1
// 	edges[i] = [ui, vi]
// 	0 <= ui, vi < n
// 	nums.length == n
// 	-5 * 104 <= nums[i] <= 5 * 104
// 	1 <= k <= 50
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
//   • When to use: Use when selecting a subset of items, each with a weight and value, to maximize total value without exceeding a given capacity. It is applicable for resource allocation problems with discrete choices.
//   • Idea: The Knapsack Problem aims to choose items with maximum total value such that their total weight does not exceed a given capacity. It is typically solved using dynamic programming, achieving a time complexity of O(nW) for n items and capacity W.
//   • Invariants: `dp[j]` (in 1D DP) represents the maximum value achievable with capacity `j` using items considered so far.; When processing item `i` and capacity `j` (decreasing `j`), `dp[j-weight_i]` holds the value from previous items for that reduced capacity.
//   • Tips: Initialize DP table with zeros for capacity 0 and unreachable states.; For 0-1 knapsack with 1D DP, iterate capacity `j` in decreasing order.
//   • Pitfalls: Incorrect iteration order for 1D DP in 0-1 knapsack (using increasing `j`).; Off-by-one errors in item indices or capacity calculations.
// - Finding bridges in a graph in O(N+M) (graph, dfs)
//   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
//   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
//   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
//   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
//   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} edges
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var subtreeInversionSum = function(edges, nums, k) {
    // Build the tree from edges
    const n = nums.length;
    const tree = Array.from({ length: n }, () => []);
    for (const [u, v] of edges) {
        tree[u].push(v);
        tree[v].push(u);
    }
    
    const mod = 1e9 + 7;
    let result = 0;
    
    const dfs = (node, parent) => {
        let count = 1;
        for (const child of tree[node]) {
            if (child !== parent) {
                count += dfs(child, node);
            }
        }
        if (count === k) {
            result = (result + nums[node]) % mod;
        }
        return count;
    };
    
    dfs(0, -1);
    return result;
};
