// Source: https://leetcode.com/problems/find-the-number-of-copy-arrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array original of length n and a 2D array bounds of length n x 2, where bounds[i] = [ui, vi].
//
// You need to find the number of possible arrays copy of length n such that:
//
//
// 	(copy[i] - copy[i - 1]) == (original[i] - original[i - 1]) for 1 <= i <= n - 1.
// 	ui <= copy[i] <= vi for 0 <= i <= n - 1.
//
//
// Return the number of such arrays.
//
// Example:
// Input: original = [1,2,3,4], bounds = [[1,2],[2,3],[3,4],[4,5]]
//
// Output: 2
//
// Explanation:
//
// The possible arrays are:
//
//
// 	[1, 2, 3, 4]
// 	[2, 3, 4, 5]
//
// Constraints:
// 2 <= n == original.length <= 105
// 	1 <= original[i] <= 109
// 	bounds.length == n
// 	bounds[i].length == 2
// 	1 <= bounds[i][0] <= bounds[i][1] <= 109
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
//   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
//   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
//   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
//   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countArrays(vector<int>& original, vector<vector<int>>& bounds) {
        const int MOD = 1e9 + 7;
        int n = original.size();
        vector<long long> diff(n - 1);
        for (int i = 1; i < n; ++i) {
            diff[i - 1] = (long long)original[i] - (long long)original[i - 1];
        }

        long long lower_bound = bounds[0][0];
        long long upper_bound = bounds[0][1];

        for (int i = 1; i < n; ++i) {
            lower_bound += diff[i - 1];
            upper_bound += diff[i - 1];

            long long curr_low = bounds[i][0];
            long long curr_high = bounds[i][1];

            lower_bound = max(lower_bound, curr_low);
            upper_bound = min(upper_bound, curr_high);

            if (lower_bound > upper_bound) {
                return 0;
            }
        }

        return (int)((upper_bound - lower_bound + 1) % MOD);            
    }
};
