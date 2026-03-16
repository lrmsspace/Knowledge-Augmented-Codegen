// Source: https://leetcode.com/problems/maximum-deletions-on-a-string/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of only lowercase English letters. In one operation, you can:
//
//
// 	Delete the entire string s, or
// 	Delete the first i letters of s if the first i letters of s are equal to the following i letters in s, for any i in the range 1 <= i <= s.length / 2.
//
//
// For example, if s = "ababc", then in one operation, you could delete the first two letters of s to get "abc", since the first two letters of s and the following two letters of s are both equal to "ab".
//
// Return the maximum number of operations needed to delete all of s.
//
// Example:
// Input: s = "abcabcdabc"
// Output: 2
// Explanation:
// - Delete the first 3 letters ("abc") since the next 3 letters are equal. Now, s = "abcdabc".
// - Delete all the letters.
// We used 2 operations so return 2. It can be proven that 2 is the maximum number of operations needed.
// Note that in the second operation we cannot delete "abc" again because the next occurrence of "abc" does not happen in the next 3 letters.
//
// Constraints:
// 1 <= s.length <= 4000
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-1d)
//   • When to use: Used for efficient string searching and pattern matching in linear time. It's also fundamental for various string algorithms that leverage self-matching properties.
//   • Idea: The prefix function computes for each position in a string the length of the longest proper prefix of its substring that is also a suffix of that substring. This forms the core of the Knuth-Morris-Pratt (KMP) algorithm, enabling linear time O(N) string matching.
//   • Invariants: For each i, pi[i] is the length of the longest proper prefix of s[0...i] that is also a suffix of s[0...i].; The current j (length of the matched prefix) always represents pi[i-1] or a shorter valid prefix length.
//   • Tips: The prefix function array (pi array) stores lengths, not indices.; It can be used to build the KMP automaton for pattern matching.
//   • Pitfalls: Confusing proper prefix/suffix with non-proper ones.; Incorrectly handling the base case pi[0] = 0.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int deleteString(string s) {
        const int n = s.size();
        const int p1 = 131, p2 = 137;
        const int m1 = 1e9 + 7, m2 = 1e9 + 9;

        vector<long long> pPower1(n + 1, 1), pPower2(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            pPower1[i] = (pPower1[i - 1] * p1) % m1;
            pPower2[i] = (pPower2[i - 1] * p2) % m2;
        }

        vector<long long> prefixHash1(n + 1, 0), prefixHash2(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixHash1[i + 1] = (prefixHash1[i] * p1 + (s[i] - 'a' + 1)) % m1;
            prefixHash2[i + 1] = (prefixHash2[i] * p2 + (s[i] - 'a' + 1)) % m2;
        }

        auto getHash = [&](int l, int r) {
            long long hash1 = (prefixHash1[r] - (prefixHash1[l] * pPower1[r - l]) % m1 + m1) % m1;
            long long hash2 = (prefixHash2[r] - (prefixHash2[l] * pPower2[r - l]) % m2 + m2) % m2;
            return make_pair(hash1, hash2);
        };

        vector<int> dp(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            dp[i] = 1;
            for (int len = 1; i + 2 * len <= n; ++len) {
                if (getHash(i, i + len) == getHash(i + len, i + 2 * len)) {
                    dp[i] = max(dp[i], 1 + dp[i + len]);
                }
            }
        }

        return dp[0];           
    }
};
