// Source: https://leetcode.com/problems/closest-equal-element-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given a circular array nums and an array queries.
//
// For each query i, you have to find the following:
//
//
// 	The minimum distance between the element at index queries[i] and any other index j in the circular array, where nums[j] == nums[queries[i]]. If no such index exists, the answer for that query should be -1.
//
//
// Return an array answer of the same size as queries, where answer[i] represents the result for query i.
//
// Example:
// Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]
//
// Output: [2,-1,3]
//
// Explanation:
//
//
// 	Query 0: The element at queries[0] = 0 is nums[0] = 1. The nearest index with the same value is 2, and the distance between them is 2.
// 	Query 1: The element at queries[1] = 3 is nums[3] = 4. No other index contains 4, so the result is -1.
// 	Query 2: The element at queries[2] = 5 is nums[5] = 3. The nearest index with the same value is 1, and the distance between them is 3 (following the circular path: 5 -> 6 -> 0 -> 1).
//
// Constraints:
// 1 <= queries.length <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	0 <= queries[i] < nums.length
//
// Helpful references (internal KB):
// - Range Minimum Query (array, sparse-table)
//   • When to use: When performing many range minimum queries on a static array, especially when query time needs to be logarithmic after initial preprocessing.
//   • Idea: A data structure that precomputes minimums for all possible ranges of power-of-two lengths, allowing O(1) query time after O(N log N) preprocessing. It efficiently answers range minimum queries on an immutable array.
//   • Invariants: For any `j`, `dp[i][j]` stores the minimum value in the segment starting at `i` with length `2^j`.; The `log_table[k]` stores `floor(log2(k))` for efficient length calculation.
//   • Tips: Precompute log values or use `std::log2` for efficient length calculations.; The `dp[i][j]` entry stores the minimum in the range `[i, i + 2^j - 1]`.
//   • Pitfalls: Does not support updates to the array elements; it's for static data only.; Higher memory consumption compared to some other range query structures.
// - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
//   • When to use: Use when you need to answer multiple Lowest Common Ancestor (LCA) queries on a static tree, and all queries are available before processing.
//   • Idea: Tarjan's off-line LCA algorithm efficiently computes the Lowest Common Ancestor for multiple pairs of nodes in a tree using a single Depth-First Search traversal combined with a Disjoint Set Union data structure, achieving nearly linear time complexity.
//   • Invariants: When DFS is at node `v`, all its children's subtrees have been fully processed and merged into `v`'s DSU set.; For any node `x` whose DFS has completed, `ancestor[find_set(x)]` stores an ancestor of `x` on the path to the root.
//   • Tips: Initialize each node as its own set in DSU with itself as the ancestor.; Process queries for a node only after its children's subtrees are fully processed.
//   • Pitfalls: Not suitable for online LCA queries or dynamic tree structures.; Incorrectly updating the `ancestor` array in the DSU can lead to wrong LCAs.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Integer> solveQueries(int[] nums, int[] queries) {
        int n = nums.length;
        Map<Integer, List<Integer>> indexMap = new HashMap<>();
        for (int i = 0; i < n; i++) {
            indexMap.computeIfAbsent(nums[i], k -> new ArrayList<>()).add(i);
        }

        List<Integer> result = new ArrayList<>();
        for (int query : queries) {
            int value = nums[query];
            List<Integer> indices = indexMap.get(value);
            if (indices.size() == 1) {
                result.add(-1);
                continue;
            }

            int minDistance = Integer.MAX_VALUE;
            for (int idx : indices) {
                if (idx != query) {
                    int distance = Math.abs(idx - query);
                    minDistance = Math.min(minDistance, Math.min(distance, n - distance));
                }
            }
            result.add(minDistance);
        }
        return result;          
    }
}
