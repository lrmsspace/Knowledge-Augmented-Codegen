// Source: https://leetcode.com/problems/minimum-penalty-for-a-shop/   |   Difficulty: Medium
//
// Problem Description:
// You are given the customer visit log of a shop represented by a 0-indexed string customers consisting only of characters 'N' and 'Y':
//
//
// 	if the ith character is 'Y', it means that customers come at the ith hour
// 	whereas 'N' indicates that no customers come at the ith hour.
//
//
// If the shop closes at the jth hour (0 <= j <= n), the penalty is calculated as follows:
//
//
// 	For every hour when the shop is open and no customers come, the penalty increases by 1.
// 	For every hour when the shop is closed and customers come, the penalty increases by 1.
//
//
// Return the earliest hour at which the shop must be closed to incur a minimum penalty.
//
// Note that if a shop closes at the jth hour, it means the shop is closed at the hour j.
//
// Example:
// Input: customers = "YYNY"
// Output: 2
// Explanation: 
// - Closing the shop at the 0th hour incurs in 1+1+0+1 = 3 penalty.
// - Closing the shop at the 1st hour incurs in 0+1+0+1 = 2 penalty.
// - Closing the shop at the 2nd hour incurs in 0+0+0+1 = 1 penalty.
// - Closing the shop at the 3rd hour incurs in 0+0+1+1 = 2 penalty.
// - Closing the shop at the 4th hour incurs in 0+0+1+0 = 1 penalty.
// Closing the shop at 2nd or 4th hour gives a minimum penalty. Since 2 is earlier, the optimal closing time is 2.
//
// Constraints:
// 1 <= customers.length <= 105
// 	customers consists only of characters 'Y' and 'N'.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Fenwick Tree (array, bit-fenwick, prefix-sum)
//   • When to use: Use when frequent point updates and range sum queries are needed on an array. It offers logarithmic time complexity for both operations, making it more efficient than a simple prefix sum array for dynamic data.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently calculates prefix sums and updates individual elements in an array. Both operations typically run in O(log N) time.
//   • Invariants: Each node `tree[i]` stores the sum of a specific range of elements ending at index `i`.; The length of the range summed by `tree[i]` is determined by `i & (-i)` (lowbit operation).
//   • Tips: Understand the lowbit operation and its role in navigating the tree structure.; Use 1-based indexing for simpler implementation of lowbit calculations.
//   • Pitfalls: Forgetting 1-based indexing can lead to off-by-one errors and incorrect results.; Incorrectly implementing the lowbit calculation or update/query logic.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int bestClosingTime(char* customers) {
    int n = 0;
    while (customers[n]) n++; // Get the length of the customers string

    int penalty = 0; // Initial penalty when the shop is closed at hour 0
    for (int i = 0; i < n; i++) {
        if (customers[i] == 'Y') {
            penalty++; // If customers come at hour i, it adds to the penalty if the shop is closed
        }
    }

    int minPenalty = penalty; // Initialize minimum penalty with the initial penalty
    int bestHour = 0; // Initialize best hour to close the shop

    for (int j = 1; j <= n; j++) {
        if (customers[j - 1] == 'Y') {
            penalty--; // If customers come at hour j-1, it reduces the penalty when we open the shop at hour j
        } else {
            penalty++; // If no customers come at hour j-1, it increases the penalty when we open the shop at hour j
        }

        if (penalty < minPenalty) {
            minPenalty = penalty; // Update minimum penalty
            bestHour = j; // Update best hour to close the shop
        }
    }

    return bestHour;        
}
