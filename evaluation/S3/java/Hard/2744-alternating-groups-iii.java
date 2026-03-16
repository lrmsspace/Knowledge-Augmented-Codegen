// Source: https://leetcode.com/problems/alternating-groups-iii/   |   Difficulty: Hard
//
// Problem Description:
// There are some red and blue tiles arranged circularly. You are given an array of integers colors and a 2D integers array queries.
//
// The color of tile i is represented by colors[i]:
//
//
//  colors[i] == 0 means that tile i is red.
//  colors[i] == 1 means that tile i is blue.
//
//
// An alternating group is a contiguous subset of tiles in the circle with alternating colors (each tile in the group except the first and last one has a different color from its adjacent tiles in the group).
//
// You have to process queries of two types:
//
//
//  queries[i] = [1, sizei], determine the count of alternating groups with size sizei.
//  queries[i] = [2, indexi, colori], change colors[indexi] to colori.
//
//
// Return an array answer containing the results of the queries of the first type in order.
//
// Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.
//
// Example:
// Input: colors = [0,1,1,0,1], queries = [[2,1,0],[1,4]]
//
// Output: [2]
//
// Explanation:
//
//
//
// First query:
//
// Change colors[1] to 0.
//
//
//
// Second query:
//
// Count of the alternating groups with size 4:
//
// Constraints:
// 4 <= colors.length <= 5 * 104
//  0 <= colors[i] <= 1
//  1 <= queries.length <= 5 * 104
//  queries[i][0] == 1 or queries[i][0] == 2
//  For all i that:
//  
//   queries[i][0] == 1: queries[i].length == 2, 3 <= queries[i][1] <= colors.length - 1
//   queries[i][0] == 2: queries[i].length == 3, 0 <= queries[i][1] <= colors.length - 1, 0 <= queries[i][2] <= 1
//
// Helpful references (internal KB):
// - Fenwick Tree (array, bit-fenwick, prefix-sum)
//   • When to use: When you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It is ideal for scenarios requiring both fast query and update operations on an array.
//   • Idea: A Fenwick tree, or Binary Indexed Tree (BIT), is an array-based data structure that efficiently calculates prefix sums and updates individual elements in an array. It supports both point updates and prefix sum queries in O(log N) time complexity.
//   • Invariants: Each `T[i]` stores the sum of a specific range `[g(i), i]` from the original array.; The `sum(idx)` function correctly aggregates values from `A[0]` to `A[idx]`.
//   • Tips: Understand the bit manipulation (`i & -i`) for navigating parent/child relationships.; Consistently choose and apply either 0-based or 1-based indexing throughout the implementation.
//   • Pitfalls: Incorrectly handling 0-based versus 1-based indexing can lead to off-by-one errors.; Forgetting to initialize the tree or performing updates incorrectly will yield wrong results.
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It provides logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure that can efficiently update individual elements and calculate prefix sums in an array. Both operations are performed in O(log N) time.
//   • Invariants: Each `tree[i]` element stores the sum of a contiguous range of elements from the original array, specifically from `i - (i & -i) + 1` to `i` (inclusive, 1-based).; After any `update(idx, val)` operation, `query(idx)` will reflect the new sum up to `idx`.
//   • Tips: Use 1-based indexing for array elements to simplify bitwise logic; The `idx & -idx` operation is key to navigating the implicit tree structure
//   • Pitfalls: Confusing 0-based and 1-based indexing can lead to incorrect results; Off-by-one errors when calculating range sums (e.g., `query(R) - query(L-1)`)
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Integer> numberOfAlternatingGroups(int[] colors, int[][] queries) {
        int n = colors.length;
        FenwickTree fenwicks = new FenwickTree(n);
        for (int i = 0; i < n; i++) {
            if (colors[i] != colors[(i + 1) % n]) {
                fenwicks.update(i, 1);
            }
        }

        List<Integer> result = new ArrayList<>();
        for (int[] query : queries) {
            if (query[0] == 1) {
                int size = query[1];
                int count = 0;
                for (int i = 0; i < n; i++) {
                    int j = (i + size - 1) % n;
                    if (fenwicks.query(j) - fenwicks.query(i - 1) == size - 1) {
                        count++;
                    }
                }
                result.add(count);
            } else {
                int index = query[1];
                int color = query[2];
                if (colors[index] != color) {
                    colors[index] = color;
                    fenwicks.update(index, color == 0 ? -1 : 1);
                    fenwicks.update((index + 1) % n, color == 0 ? -1 : 1);
                }
            }
        }

        return result;          
    }
}
