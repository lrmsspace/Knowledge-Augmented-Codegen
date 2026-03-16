// Source: https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums.
//
// The distinct count of a subarray of nums is defined as:
//
//
// 	Let nums[i..j] be a subarray of nums consisting of all the indices from i to j such that 0 <= i <= j < nums.length. Then the number of distinct values in nums[i..j] is called the distinct count of nums[i..j].
//
//
// Return the sum of the squares of distinct counts of all subarrays of nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,1]
// Output: 15
// Explanation: Six possible subarrays are:
// [1]: 1 distinct value
// [2]: 1 distinct value
// [1]: 1 distinct value
// [1,2]: 2 distinct values
// [2,1]: 2 distinct values
// [1,2,1]: 2 distinct values
// The sum of the squares of the distinct counts in all subarrays is equal to 12 + 12 + 12 + 22 + 22 + 22 = 15.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree)
//   • When to use: Use when you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in logarithmic time.
//   • Idea: A Segment Tree is a tree-based data structure that stores information about array intervals, enabling efficient O(log n) range queries and point/range updates.
//   • Invariants: Each node in the segment tree represents a contiguous subsegment of the original array.; The value stored in a non-leaf node is an aggregation of the values from its direct children.
//   • Tips: Build the tree recursively, dividing the array into halves.; Use lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors when defining segment boundaries or array indices.; Forgetting to push down lazy tags before querying or updating children nodes.
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
//   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
//   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
//   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
//   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
//   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int sumCounts(int[] nums) {
        int n = nums.length;
        int mod = 1_000_000_007;

        // Step 1: Calculate the last occurrence of each number
        int[] lastOccurrence = new int[100001];
        for (int i = 0; i < n; i++) {
            lastOccurrence[nums[i]] = i + 1; // Store 1-based index
        }

        // Step 2: Use a Fenwick Tree to calculate the sum of squares of distinct counts
        FenwickTree fenwickTree = new FenwickTree(n);
        long result = 0;

        for (int i = 0; i < n; i++) {
            int num = nums[i];
            int lastIndex = lastOccurrence[num];

            // Update the Fenwick Tree with the contribution of the current number
            fenwickTree.update(lastIndex, 1); // Increment count for this number

            // Calculate the contribution of this number to the result
            long countDistinct = fenwickTree.query(i + 1); // Get count of distinct numbers up to index i
            result = (result + countDistinct * countDistinct) % mod;
        }

        return (int) result;            
    }
}
