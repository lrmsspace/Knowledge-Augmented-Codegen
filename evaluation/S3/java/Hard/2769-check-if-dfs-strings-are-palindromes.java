// Source: https://leetcode.com/problems/check-if-dfs-strings-are-palindromes/   |   Difficulty: Hard
//
// Problem Description:
// You are given a tree rooted at node 0, consisting of n nodes numbered from 0 to n - 1. The tree is represented by an array parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] == -1.
//
// You are also given a string s of length n, where s[i] is the character assigned to node i.
//
// Consider an empty string dfsStr, and define a recursive function dfs(int x) that takes a node x as a parameter and performs the following steps in order:
//
//
// 	Iterate over each child y of x in increasing order of their numbers, and call dfs(y).
// 	Add the character s[x] to the end of the string dfsStr.
//
//
// Note that dfsStr is shared across all recursive calls of dfs.
//
// You need to find a boolean array answer of size n, where for each index i from 0 to n - 1, you do the following:
//
//
// 	Empty the string dfsStr and call dfs(i).
// 	If the resulting string dfsStr is a palindrome, then set answer[i] to true. Otherwise, set answer[i] to false.
//
//
// Return the array answer.
//
// Example:
// Input: parent = [-1,0,0,1,1,2], s = "aababa"
//
// Output: [true,true,false,true,true,true]
//
// Explanation:
//
//
// 	Calling dfs(0) results in the string dfsStr = "abaaba", which is a palindrome.
// 	Calling dfs(1) results in the string dfsStr = "aba", which is a palindrome.
// 	Calling dfs(2) results in the string dfsStr = "ab", which is not a palindrome.
// 	Calling dfs(3) results in the string dfsStr = "a", which is a palindrome.
// 	Calling dfs(4) results in the string dfsStr = "b", which is a palindrome.
// 	Calling dfs(5) results in the string dfsStr = "a", which is a palindrome.
//
// Constraints:
// n == parent.length == s.length
// 	1 <= n <= 105
// 	0 <= parent[i] <= n - 1 for all i >= 1.
// 	parent[0] == -1
// 	parent represents a valid tree.
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Finding articulation points in a graph in O(N+M) (graph, array, dfs)
//   • When to use: Use when identifying critical nodes whose removal would increase the number of connected components in an undirected graph. It's essential for analyzing network robustness and vulnerability.
//   • Idea: This algorithm finds all articulation points (cut vertices) in an undirected graph using a single Depth First Search traversal. It operates in linear time, O(N+M), where N is vertices and M is edges.
//   • Invariants: For any node `u`, `tin[u]` is its discovery time, and `low[u]` is initialized to `tin[u]`.; After visiting all children `v` of `u` (and their subtrees), `low[u]` will hold the minimum `tin` value reachable from `u` or its descendants via tree edges and at most one back-edge.
//   • Tips: Initialize `tin` (discovery time) and `low` (lowest reachable ancestor) arrays for all vertices.; The root of the DFS tree is an articulation point if it has more than one child in the DFS tree.
//   • Pitfalls: Forgetting to initialize `low[u]` with `tin[u]` before processing children.; Incorrectly applying the `tin[u] <= low[v]` condition to the root node of the DFS tree.
// - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
//   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
//   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
//   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
//   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
//   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean[] findAnswer(int[] parent, String s) {
        int n = parent.length;
        List<List<Integer>> tree = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            tree.add(new ArrayList<>());
        }
        for (int i = 1; i < n; i++) {
            tree.get(parent[i]).add(i);
        }

        boolean[] answer = new boolean[n];
        StringBuilder dfsStr = new StringBuilder();
        for (int i = 0; i < n; i++) {
            dfsStr.setLength(0); // Clear the string builder
            dfs(i, tree, s, dfsStr);
            answer[i] = isPalindrome(dfsStr);
        }
        return answer;          
    }
}
