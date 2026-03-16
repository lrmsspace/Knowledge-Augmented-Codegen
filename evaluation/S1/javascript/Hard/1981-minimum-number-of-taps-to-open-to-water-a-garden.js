// Source: https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/   |   Difficulty: Hard
//
// Problem Description:
// There is a one-dimensional garden on the x-axis. The garden starts at the point 0 and ends at the point n. (i.e., the length of the garden is n).
//
// There are n + 1 taps located at points [0, 1, ..., n] in the garden.
//
// Given an integer n and an integer array ranges of length n + 1 where ranges[i] (0-indexed) means the i-th tap can water the area [i - ranges[i], i + ranges[i]] if it was open.
//
// Return the minimum number of taps that should be open to water the whole garden, If the garden cannot be watered return -1.
//
// Example:
// Input: n = 5, ranges = [3,4,1,1,0,0]
// Output: 1
// Explanation: The tap at point 0 can cover the interval [-3,3]
// The tap at point 1 can cover the interval [-3,5]
// The tap at point 2 can cover the interval [1,3]
// The tap at point 3 can cover the interval [2,4]
// The tap at point 4 can cover the interval [4,4]
// The tap at point 5 can cover the interval [5,5]
// Opening Only the second tap will water the whole garden [0,5]
//
// Constraints:
// 1 <= n <= 104
// 	ranges.length == n + 1
// 	0 <= ranges[i] <= 100
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Range Minimum Query (array, sparse-table)
//   • When to use: When performing many range minimum queries on a static array, especially when query time needs to be logarithmic after initial preprocessing.
//   • Idea: A data structure that precomputes minimums for all possible ranges of power-of-two lengths, allowing O(1) query time after O(N log N) preprocessing. It efficiently answers range minimum queries on an immutable array.
//   • Invariants: For any `j`, `dp[i][j]` stores the minimum value in the segment starting at `i` with length `2^j`.; The `log_table[k]` stores `floor(log2(k))` for efficient length calculation.
//   • Tips: Precompute log values or use `std::log2` for efficient length calculations.; The `dp[i][j]` entry stores the minimum in the range `[i, i + 2^j - 1]`.
//   • Pitfalls: Does not support updates to the array elements; it's for static data only.; Higher memory consumption compared to some other range query structures.
// - Linear Diophantine Equation (number, greedy)
//   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
//   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
//   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
//   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
//   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[]} ranges
 * @return {number}
 */
var minTaps = function(n, ranges) {
    const intervals = [];
    for (let i = 0; i <= n; i++) {
        const left = Math.max(0, i - ranges[i]);
        const right = Math.min(n, i + ranges[i]);
        intervals.push([left, right]);
    }

    intervals.sort((a, b) => a[0] - b[0]);

    let taps = 0;
    let currentEnd = 0;
    let farthestEnd = 0;
    let i = 0;

    while (currentEnd < n) {
        while (i < intervals.length && intervals[i][0] <= currentEnd) {
            farthestEnd = Math.max(farthestEnd, intervals[i][1]);
            i++;
        }
        if (farthestEnd <= currentEnd) {
            return -1;
        }
        taps++;
        currentEnd = farthestEnd;
    }

    return taps;
};
