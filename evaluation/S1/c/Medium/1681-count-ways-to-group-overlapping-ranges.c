// Source: https://leetcode.com/problems/count-ways-to-group-overlapping-ranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array ranges where ranges[i] = [starti, endi] denotes that all integers between starti and endi (both inclusive) are contained in the ith range.
//
// You are to split ranges into two (possibly empty) groups such that:
//
//
// 	Each range belongs to exactly one group.
// 	Any two overlapping ranges must belong to the same group.
//
//
// Two ranges are said to be overlapping if there exists at least one integer that is present in both ranges.
//
//
// 	For example, [1, 3] and [2, 5] are overlapping because 2 and 3 occur in both ranges.
//
//
// Return the total number of ways to split ranges into two groups. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: ranges = [[6,10],[5,15]]
// Output: 2
// Explanation: 
// The two ranges are overlapping, so they must be in the same group.
// Thus, there are two possible ways:
// - Put both the ranges together in group 1.
// - Put both the ranges together in group 2.
//
// Constraints:
// 1 <= ranges.length <= 105
// 	ranges[i].length == 2
// 	0 <= starti <= endi <= 109
//
// Helpful references (internal KB):
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Binomial Coefficients (array, number, mod-exp, enumeration)
//   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
//   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
//   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
//   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
//   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countWays(int** ranges, int rangesSize, int* rangesColSize) {
    // Sort ranges by starting point
    qsort(ranges, rangesSize, sizeof(int*), [](const void* a, const void* b) {
        int* rangeA = *(int**)a;
        int* rangeB = *(int**)b;
        return rangeA[0] - rangeB[0];
    });

    long long mod = 1000000007;
    int groups = 0;
    int currentEnd = -1;

    for (int i = 0; i < rangesSize; i++) {
        if (ranges[i][0] > currentEnd) {
            groups++;
            currentEnd = ranges[i][1];
        } else {
            if (ranges[i][1] > currentEnd) {
                currentEnd = ranges[i][1];
            }
        }
    }

    long long result = 1;
    for (int i = 0; i < groups; i++) {
        result = (result * 2) % mod;
    }

    return (int)result;     
}
