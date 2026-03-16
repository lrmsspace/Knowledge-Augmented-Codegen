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
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int longestAwesome(char* s) {
    int pos[1024];
    for (int i = 0; i < 1024; ++i) pos[i] = -1;
    pos[0] = 0;

    int state = 0;
    int maxLen = 0;
    for (int i = 0; s[i]; ++i) {
        state ^= (1 << (s[i] - '0'));

        /* check for exact match */
        if (pos[state] >= 0) {
            int len = i + 1 - pos[state];
            if (len > maxLen) maxLen = len;
        } else {
            pos[state] = i + 1;
        }

        /* check for one bit difference */
        for (int b = 0; b < 10; ++b) {
            int toggledState = state ^ (1 << b);
            if (pos[toggledState] >= 0) {
                int len = i + 1 - pos[toggledState];
                if (len > maxLen) maxLen = len;
            }
        }
    }

    return maxLen;      
}
