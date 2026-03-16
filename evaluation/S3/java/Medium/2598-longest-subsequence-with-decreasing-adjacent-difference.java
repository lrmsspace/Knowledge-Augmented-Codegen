// Source: https://leetcode.com/problems/longest-subsequence-with-decreasing-adjacent-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums.
//
// Your task is to find the length of the longest subsequence seq of nums, such that the absolute differences between consecutive elements form a non-increasing sequence of integers. In other words, for a subsequence seq0, seq1, seq2, ..., seqm of nums, |seq1 - seq0| >= |seq2 - seq1| >= ... >= |seqm - seqm - 1|.
//
// Return the length of such a subsequence.
//
// Example:
// Input: nums = [16,6,3]
//
// Output: 3
//
// Explanation: 
//
// The longest subsequence is [16, 6, 3] with the absolute adjacent differences [10, 3].
//
// Constraints:
// 2 <= nums.length <= 104
// 	1 <= nums[i] <= 300
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, divide-and-conquer)
//   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
//   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
//   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
//   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
// - Range Minimum Query (array, tree, segment-tree)
//   • When to use: Use when needing to efficiently query minimums over arbitrary ranges and perform point or range updates on an array.
//   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and performing updates in logarithmic time, typically O(log N) for both.
//   • Invariants: Each node in the segment tree represents a contiguous subsegment of the original array.; A parent node's value is derived from its children's values (e.g., minimum of children).
//   • Tips: Build the tree recursively, dividing the array into halves until leaf nodes are reached.; Query operations involve traversing relevant segments, combining results from child nodes.
//   • Pitfalls: Incorrectly handling array indexing (0-based vs. 1-based) can lead to off-by-one errors.; Forgetting to update parent nodes after a child's value changes during an update operation.
// - Segment Tree (tree, array, segment-tree)
//   • When to use: Use when you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in logarithmic time.
//   • Idea: A Segment Tree is a tree-based data structure that stores information about array intervals, enabling efficient O(log n) range queries and point/range updates.
//   • Invariants: Each node in the segment tree represents a contiguous subsegment of the original array.; The value stored in a non-leaf node is an aggregation of the values from its direct children.
//   • Tips: Build the tree recursively, dividing the array into halves.; Use lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors when defining segment boundaries or array indices.; Forgetting to push down lazy tags before querying or updating children nodes.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int longestSubsequence(int[] nums) {
        int n = nums.length;
        int[] dp = new int[n];
        Arrays.fill(dp, 1); // Initialize all subsequences to length 1

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (Math.abs(nums[i] - nums[j]) <= Math.abs(nums[j] - nums[Math.max(0, j - 1)])) {
                    dp[i] = Math.max(dp[i], dp[j] + 1);
                }
            }
        }

        int maxLength = 0;
        for (int length : dp) {
            maxLength = Math.max(maxLength, length);
        }

        return maxLength;           
    }
}
