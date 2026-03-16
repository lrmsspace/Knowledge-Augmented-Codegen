// Source: https://leetcode.com/problems/longest-chunked-palindrome-decomposition/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string text. You should split it to k substrings (subtext1, subtext2, ..., subtextk) such that:
//
//
// 	subtexti is a non-empty string.
// 	The concatenation of all the substrings is equal to text (i.e., subtext1 + subtext2 + ... + subtextk == text).
// 	subtexti == subtextk - i + 1 for all valid values of i (i.e., 1 <= i <= k).
//
//
// Return the largest possible value of k.
//
// Example:
// Input: text = "ghiabcdefhelloadamhelloabcdefghi"
// Output: 7
// Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".
//
// Constraints:
// 1 <= text.length <= 1000
// 	text consists only of lowercase English characters.
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Suffix Array (string, array, merge-sort)
//   • When to use: Use when needing to efficiently query properties of all suffixes or substrings of a given text, especially for pattern matching or finding repeated structures. It is particularly useful for problems requiring lexicographical ordering of all suffixes.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices. It enables efficient string operations like pattern searching and finding longest common prefixes, typically constructed in O(N log N) time.
//   • Invariants: After k iterations, suffixes are sorted correctly up to a certain length (e.g., 2^k).; All suffixes of the original string are represented by their starting indices in the array.
//   • Tips: Append a unique sentinel character (e.g., '$') smaller than any other character to the string.; Utilize the LCP array, often built alongside, for advanced string queries and optimizations.
//   • Pitfalls: Naive sorting of suffixes by string comparison leads to an inefficient O(N^2 log N) complexity.; High memory usage for very long strings due to storing all suffixes implicitly or explicitly.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int longestDecomposition(string text) {
        int n = text.size();
        const int p = 131;
        const int mod1 = 1e9 + 7;
        const int mod2 = 1e9 + 9;

        vector<long long> p_power1(n + 1, 1), p_power2(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            p_power1[i] = (p_power1[i - 1] * p) % mod1;
            p_power2[i] = (p_power2[i - 1] * p) % mod2;
        }

        vector<long long> prefix_hash1(n + 1, 0), prefix_hash2(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix_hash1[i + 1] = (prefix_hash1[i] * p + (text[i] - 'a' + 1)) % mod1;
            prefix_hash2[i + 1] = (prefix_hash2[i] * p + (text[i] - 'a' + 1)) % mod2;
        }

        auto get_hash = [&](int l, int r) {
            long long hash1 = (prefix_hash1[r + 1] - (prefix_hash1[l] * p_power1[r - l + 1]) % mod1 + mod1) % mod1;
            long long hash2 = (prefix_hash2[r + 1] - (prefix_hash2[l] * p_power2[r - l + 1]) % mod2 + mod2) % mod2;
            return make_pair(hash1, hash2);
        };

        int left = 0, right = n - 1;
        int count = 0;

        while (left <= right) {
            bool found = false;
            for (int len = 1; left + len - 1 < right - len + 1; ++len) {
                if (get_hash(left, left + len - 1) == get_hash(right - len + 1, right)) {
                    count += 2;
                    left += len;
                    right -= len;
                    found = true;
                    break;
                }
            }
            if (!found) {
                count += 1;
                break;
            }
        }
        return count;
    }
};
