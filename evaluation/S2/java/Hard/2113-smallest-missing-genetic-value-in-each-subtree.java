// Source: https://leetcode.com/problems/smallest-missing-genetic-value-in-each-subtree/   |   Difficulty: Hard
//
// Problem Description:
// There is a family tree rooted at 0 consisting of n nodes numbered 0 to n - 1. You are given a 0-indexed integer array parents, where parents[i] is the parent for node i. Since node 0 is the root, parents[0] == -1.
//
// There are 105 genetic values, each represented by an integer in the inclusive range [1, 105]. You are given a 0-indexed integer array nums, where nums[i] is a distinct genetic value for node i.
//
// Return an array ans of length n where ans[i] is the smallest genetic value that is missing from the subtree rooted at node i.
//
// The subtree rooted at a node x contains node x and all of its descendant nodes.
//
// Example:
// Input: parents = [-1,0,0,2], nums = [1,2,3,4]
// Output: [5,1,1,1]
// Explanation: The answer for each subtree is calculated as follows:
// - 0: The subtree contains nodes [0,1,2,3] with values [1,2,3,4]. 5 is the smallest missing value.
// - 1: The subtree contains only node 1 with value 2. 1 is the smallest missing value.
// - 2: The subtree contains nodes [2,3] with values [3,4]. 1 is the smallest missing value.
// - 3: The subtree contains only node 3 with value 4. 1 is the smallest missing value.
//
// Constraints:
// n == parents.length == nums.length
// 	2 <= n <= 105
// 	0 <= parents[i] <= n - 1 for i != 0
// 	parents[0] == -1
// 	parents represents a valid tree.
// 	1 <= nums[i] <= 105
// 	Each nums[i] is distinct.
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (tree, binary-search)
//   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
//   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
//   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
//   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
//   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
// - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
//   • When to use: Use when you need to answer multiple Lowest Common Ancestor (LCA) queries on a static tree, and all queries are available before processing.
//   • Idea: Tarjan's off-line LCA algorithm efficiently computes the Lowest Common Ancestor for multiple pairs of nodes in a tree using a single Depth-First Search traversal combined with a Disjoint Set Union data structure, achieving nearly linear time complexity.
//   • Invariants: When DFS is at node `v`, all its children's subtrees have been fully processed and merged into `v`'s DSU set.; For any node `x` whose DFS has completed, `ancestor[find_set(x)]` stores an ancestor of `x` on the path to the root.
//   • Tips: Initialize each node as its own set in DSU with itself as the ancestor.; Process queries for a node only after its children's subtrees are fully processed.
//   • Pitfalls: Not suitable for online LCA queries or dynamic tree structures.; Incorrectly updating the `ancestor` array in the DSU can lead to wrong LCAs.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] smallestMissingValueSubtree(int[] parents, int[] nums) {
        int n = parents.length;
        int[] ans = new int[n];
        Arrays.fill(ans, 1);
        Map<Integer, List<Integer>> graph = new HashMap<>();
        for (int i = 0; i < n; i++) {
            graph.computeIfAbsent(parents[i], k -> new ArrayList<>()).add(i);
        }
        if (!graph.containsKey(0)) {
            return ans;
        }
        Set<Integer> seen = new HashSet<>();
        int node = 0;
        while (node != -1) {
            dfs(graph, node, seen, nums);
            while (seen.contains(ans[node])) {
                ans[node]++;
            }
            node = parents[node];
        }
        return ans;         
    }
}
