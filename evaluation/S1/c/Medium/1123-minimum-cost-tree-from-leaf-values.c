// Source: https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/   |   Difficulty: Medium
//
// Problem Description:
// Given an array arr of positive integers, consider all binary trees such that:
//
//
// 	Each node has either 0 or 2 children;
// 	The values of arr correspond to the values of each leaf in an in-order traversal of the tree.
// 	The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree, respectively.
//
//
// Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node. It is guaranteed this sum fits into a 32-bit integer.
//
// A node is a leaf if and only if it has zero children.
//
// Example:
// Input: arr = [6,2,4]
// Output: 32
// Explanation: There are two possible trees shown.
// The first has a non-leaf node sum 36, and the second has non-leaf node sum 32.
//
// Constraints:
// 2 <= arr.length <= 40
// 	1 <= arr[i] <= 15
// 	It is guaranteed that the answer fits into a 32-bit signed integer (i.e., it is less than 231).
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
// - Sparse Table (array, sparse-table, dp-2d)
//   • When to use: Use when you need to answer range queries, especially Range Minimum/Maximum Queries, on an immutable array very quickly. It is ideal for scenarios where the data does not change and query performance is critical.
//   • Idea: Sparse Table is a data structure that precomputes answers for all range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like Range Minimum/Maximum Queries on a static array, with O(N log N) precomputation.
//   • Invariants: st[k][i] holds the result for the segment starting at index i with length 2^k.; For any k > 0, st[k][i] combines the results of two adjacent segments of length 2^(k-1).
//   • Tips: Precompute log2 values to find the largest power of two in O(1).; Best suited for idempotent operations like minimum, maximum, or GCD.
//   • Pitfalls: Does not support array updates; any modification invalidates the structure.; Inefficient for non-idempotent operations like range sum or XOR in O(1).
// - Range Minimum Query (array, tree, segment-tree)
//   • When to use: Use when needing to efficiently query minimums over arbitrary ranges and perform point or range updates on an array.
//   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and performing updates in logarithmic time, typically O(log N) for both.
//   • Invariants: Each node in the segment tree represents a contiguous subsegment of the original array.; A parent node's value is derived from its children's values (e.g., minimum of children).
//   • Tips: Build the tree recursively, dividing the array into halves until leaf nodes are reached.; Query operations involve traversing relevant segments, combining results from child nodes.
//   • Pitfalls: Incorrectly handling array indexing (0-based vs. 1-based) can lead to off-by-one errors.; Forgetting to update parent nodes after a child's value changes during an update operation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int mctFromLeafValues(int* arr, int arrSize) {
    int dp[arrSize][arrSize];
    int maxLeaf[arrSize][arrSize];

    // Precompute max leaf values for all intervals
    for (int i = 0; i < arrSize; i++) {
        maxLeaf[i][i] = arr[i];
        for (int j = i + 1; j < arrSize; j++) {
            if (arr[j] > maxLeaf[i][j - 1]) {
                maxLeaf[i][j] = arr[j];
            } else {
                maxLeaf[i][j] = maxLeaf[i][j - 1];
            }
        }
    }

    // Initialize dp array
    for (int i = 0; i < arrSize; i++) {
        for (int j = 0; j < arrSize; j++) {
            dp[i][j] = 0;
        }
    }

    // Fill dp array using interval DP
    for (int length = 2; length <= arrSize; length++) {
        for (int i = 0; i <= arrSize - length; i++) {
            int j = i + length - 1;
            dp[i][j] = __INT_MAX__;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + maxLeaf[i][k] * maxLeaf[k + 1][j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    return dp[0][arrSize - 1];      
}
