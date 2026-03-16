// Source: https://leetcode.com/problems/plates-between-candles/   |   Difficulty: Medium
//
// Problem Description:
// There is a long table with a line of plates and candles arranged on top of it. You are given a 0-indexed string s consisting of characters '*' and '|' only, where a '*' represents a plate and a '|' represents a candle.
//
// You are also given a 0-indexed 2D integer array queries where queries[i] = [lefti, righti] denotes the substring s[lefti...righti] (inclusive). For each query, you need to find the number of plates between candles that are in the substring. A plate is considered between candles if there is at least one candle to its left and at least one candle to its right in the substring.
//
//
// 	For example, s = "||**||**|*", and a query [3, 8] denotes the substring "*||**|". The number of plates between candles in this substring is 2, as each of the two plates has at least one candle in the substring to its left and right.
//
//
// Return an integer array answer where answer[i] is the answer to the ith query.
//
// Example:
// Input: s = "**|**|***|", queries = [[2,5],[5,9]]
// Output: [2,3]
// Explanation:
// - queries[0] has two plates between candles.
// - queries[1] has three plates between candles.
//
// Constraints:
// 3 <= s.length <= 105
// 	s consists of '*' and '|' characters.
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	0 <= lefti <= righti < s.length
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when you need to perform many range queries on a static array, especially when the query operation is associative and idempotent, allowing for O(1) query time after O(N log N) precomputation.
//   • Idea: A Sparse Table is a data structure that precomputes answers for all possible range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like min/max/gcd and O(log N) for non-idempotent associative operations, after an O(N log N) build time.
//   • Invariants: After precomputation, dp[k][i] stores the result for the range [i, i + 2^k - 1].; For any k > 0, dp[k][i] is the result of combining dp[k-1][i] and dp[k-1][i + 2^(k-1)].
//   • Tips: Precompute log2 values for faster range length calculations.; Store dp[k][i] as the result for range [i, i + 2^k - 1].
//   • Pitfalls: Does not support updates to array elements efficiently.; Requires O(N log N) space, which can be significant for large N.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @param {number[][]} queries
 * @return {number[]}
 */
var platesBetweenCandles = function(s, queries) {
    const n = s.length;
    const prefixPlates = new Array(n + 1).fill(0);
    const leftCandle = new Array(n).fill(-1);
    const rightCandle = new Array(n).fill(-1);

    // Precompute prefix sums of plates and nearest candles
    let lastCandle = -1;
    for (let i = 0; i < n; i++) {
        prefixPlates[i + 1] = prefixPlates[i] + (s[i] === '*' ? 1 : 0);
        if (s[i] === '|') {
            lastCandle = i;
        }
        leftCandle[i] = lastCandle;
    }

    lastCandle = -1;
    for (let i = n - 1; i >= 0; i--) {
        if (s[i] === '|') {
            lastCandle = i;
        }
        rightCandle[i] = lastCandle;
    }

    const result = [];
    for (const [left, right] of queries) {
        const leftBound = rightCandle[left];
        const rightBound = leftCandle[right];
        if (leftBound !== -1 && rightBound !== -1 && leftBound < rightBound) {
            result.push(prefixPlates[rightBound + 1] - prefixPlates[leftBound]);
        } else {
            result.push(0);
        }
    }

    return result;
};
