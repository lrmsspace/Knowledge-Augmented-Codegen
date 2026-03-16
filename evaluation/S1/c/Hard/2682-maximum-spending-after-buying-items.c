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
// - Priority Queues (heap, stack, heap-select)
//   • When to use: Use when you need to efficiently retrieve the element with the highest (or lowest) priority from a collection, especially when elements are added or removed frequently.
//   • Idea: A priority queue is a data structure that allows efficient retrieval of the element with the highest or lowest priority, and efficient insertion of new elements. Operations typically run in logarithmic time, O(log N).
//   • Invariants: The priority queue maintains the heap property: parent nodes are always greater than/equal to (or less than/equal to) their children.; For a K-selection problem, the priority queue contains at most K elements, representing the K largest/smallest seen so far.
//   • Tips: Use a min-priority queue to find the K largest elements by keeping at most K elements.; Use a max-priority queue to find the K smallest elements by keeping at most K elements.
//   • Pitfalls: Confusing min-priority queue with max-priority queue for the desired extremum.; Inefficient underlying implementation leading to O(N) operations instead of O(log N).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long maxSpending(int** values, int valuesSize, int* valuesColSize) {
    int m = valuesSize;
    int n = valuesColSize[0];
    long long total = 0;
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            total += (long long)values[i][j] * (j + 1);
        }
    }
    return total;       
}
