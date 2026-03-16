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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> maxTable(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            maxTable[i][i] = arr[i];
            for (int j = i + 1; j < n; ++j) {
                maxTable[i][j] = max(maxTable[i][j - 1], arr[j]);
            }
        }

        vector<vector<int>> dp(n, vector<int>(n, INT32_MAX));
        for (int length = 1; length <= n; ++length) {
            for (int i = 0; i + length - 1 < n; ++i) {
                int j = i + length - 1;
                if (i == j) {
                    dp[i][j] = 0;
                } else {
                    for (int k = i; k < j; ++k) {
                        dp[i][j] = min(dp[i][j],
                                       dp[i][k] + dp[k + 1][j] +
                                       maxTable[i][k] * maxTable[k + 1][j]);
                    }
                }
            }
        }

        return dp[0][n - 1];            
    }
};
