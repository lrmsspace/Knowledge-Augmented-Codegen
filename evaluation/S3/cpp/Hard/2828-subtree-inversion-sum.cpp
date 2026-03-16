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
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k) {
            int n = nums.size();
            vector<vector<int>> graph(n);
            for (const auto& edge : edges) {
                graph[edge[0]].push_back(edge[1]);
                graph[edge[1]].push_back(edge[0]);
            }
            vector<int> depth(n), parent(n, -1);
            function<void(int, int)> dfs = [&](int node, int par) {
                for (int neighbor : graph[node]) {
                    if (neighbor != par) {
                        depth[neighbor] = depth[node] + 1;
                        parent[neighbor] = node;
                        dfs(neighbor, node);
                    }
                }
            };
            dfs(0, -1);
            vector<long long> dp(n);
            function<void(int)> postOrder = [&](int node) {
                dp[node] = nums[node];
                for (int neighbor : graph[node]) {
                    if (neighbor != parent[node]) {
                        postOrder(neighbor);
                        if (depth[neighbor] - depth[node] >= k) {
                            dp[node] += max(0LL, dp[neighbor]);
                        }
                    }
                }
            };
            postOrder(0);
            return dp[0];
    }
};
