// Source: https://leetcode.com/problems/find-longest-awesome-substring/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s. An awesome substring is a non-empty substring of s such that we can make any number of swaps in order to make it a palindrome.
//
// Return the length of the maximum length awesome substring of s.
//
// Example:
// Input: s = "3242415"
// Output: 5
// Explanation: "24241" is the longest awesome substring, we can form the palindrome "24142" with some swaps.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of digits.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-1d)
//   • When to use: Used for efficient string searching and pattern matching in linear time. It's also fundamental for various string algorithms that leverage self-matching properties.
//   • Idea: The prefix function computes for each position in a string the length of the longest proper prefix of its substring that is also a suffix of that substring. This forms the core of the Knuth-Morris-Pratt (KMP) algorithm, enabling linear time O(N) string matching.
//   • Invariants: For each i, pi[i] is the length of the longest proper prefix of s[0...i] that is also a suffix of s[0...i].; The current j (length of the matched prefix) always represents pi[i-1] or a shorter valid prefix length.
//   • Tips: The prefix function array (pi array) stores lengths, not indices.; It can be used to build the KMP automaton for pattern matching.
//   • Pitfalls: Confusing proper prefix/suffix with non-proper ones.; Incorrectly handling the base case pi[0] = 0.
// - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
//   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
//   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
//   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
//   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
//   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int longestAwesome(String s) {
        int n = s.length();
        int[] pos = new int[1 << 10];
        for (int i = 0; i < pos.length; i++) {
            pos[i] = -1;
        }
        pos[0] = 0;

        int mask = 0;
        int res = 1;
        for (int i = 0; i < n; i++) {
            int digit = s.charAt(i) - '0';
            mask ^= (1 << digit);

            if (pos[mask] >= 0) {
                res = Math.max(res, i + 1 - pos[mask]);
            } else {
                pos[mask] = i + 1;
            }

            for (int d = 0; d < 10; d++) {
                int checkMask = mask ^ (1 << d);
                if (pos[checkMask] >= 0) {
                    res = Math.max(res, i + 1 - pos[checkMask]);
                }
            }
        }

        return res;         
    }
}
