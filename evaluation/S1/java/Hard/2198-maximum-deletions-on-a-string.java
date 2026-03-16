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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int deleteString(String s) {
        int n = s.length();
        int[] dp = new int[n + 1];
        dp[n] = 0;

        // Precompute powers of p and prefix hashes for string hashing
        long p = 131;
        long mod = 1_000_000_007;
        long[] pPower = new long[n + 1];
        long[] prefixHash = new long[n + 1];
        pPower[0] = 1;
        for (int i = 1; i <= n; i++) {
            pPower[i] = (pPower[i - 1] * p) % mod;
            prefixHash[i] = (prefixHash[i - 1] * p + s.charAt(i - 1)) % mod;
        }

        // Function to get hash of substring s[l:r]
        java.util.function.BiFunction<Integer, Integer, Long> getHash = (l, r) -> {
            long hashValue = (prefixHash[r] - (prefixHash[l] * pPower[r - l]) % mod + mod) % mod;
            return hashValue;
        };

        for (int i = n - 1; i >= 0; i--) {
            dp[i] = 1; // At least we can delete the whole string in one operation
            for (int len = 1; i + 2 * len <= n; len++) {
                if (getHash.apply(i, i + len).equals(getHash.apply(i + len, i + 2 * len))) {
                    dp[i] = Math.max(dp[i], 1 + dp[i + len]);
                }
            }
        }

        return dp[0];           
    }
}
