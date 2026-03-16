// Source: https://leetcode.com/problems/maximum-spending-after-buying-items/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed m * n integer matrix values, representing the values of m * n different items in m different shops. Each shop has n items where the jth item in the ith shop has a value of values[i][j]. Additionally, the items in the ith shop are sorted in non-increasing order of value. That is, values[i][j] >= values[i][j + 1] for all 0 <= j < n - 1.
//
// On each day, you would like to buy a single item from one of the shops. Specifically, On the dth day you can:
//
//
// 	Pick any shop i.
// 	Buy the rightmost available item j for the price of values[i][j] * d. That is, find the greatest index j such that item j was never bought before, and buy it for the price of values[i][j] * d.
//
//
// Note that all items are pairwise different. For example, if you have bought item 0 from shop 1, you can still buy item 0 from any other shop.
//
// Return the maximum amount of money that can be spent on buying all  m * n products.
//
// Example:
// Input: values = [[8,5,2],[6,4,1],[9,7,3]]
// Output: 285
// Explanation: On the first day, we buy product 2 from shop 1 for a price of values[1][2] * 1 = 1.
// On the second day, we buy product 2 from shop 0 for a price of values[0][2] * 2 = 4.
// On the third day, we buy product 2 from shop 2 for a price of values[2][2] * 3 = 9.
// On the fourth day, we buy product 1 from shop 1 for a price of values[1][1] * 4 = 16.
// On the fifth day, we buy product 1 from shop 0 for a price of values[0][1] * 5 = 25.
// On the sixth day, we buy product 0 from shop 1 for a price of values[1][0] * 6 = 36.
// On the seventh day, we buy product 1 from shop 2 for a price of values[2][1] * 7 = 49.
// On the eighth day, we buy product 0 from shop 0 for a price of values[0][0] * 8 = 64.
// On the ninth day, we buy product 0 from shop 2 for a price of values[2][0] * 9 = 81.
// Hence, our total spending is equal to 285.
// It can be shown that 285 is the maximum amount of money that can be spent buying all m * n products.
//
// Constraints:
// 1 <= m == values.length <= 10
// 	1 <= n == values[i].length <= 104
// 	1 <= values[i][j] <= 106
// 	values[i] are sorted in non-increasing order.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long maxSpending(int** values, int valuesSize, int* valuesColSize) {
    int m = valuesSize, n = valuesColSize[0];
    long long totalSpending = 0;

    // Calculate the total spending by buying items in the optimal order
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            // Calculate the day number (1-based index)
            int day = j * m + i + 1;
            // Add the cost of buying the item on this day
            totalSpending += (long long)values[i][j] * day;
        }
    }

    return totalSpending;       
}
