// Source: https://leetcode.com/problems/replace-question-marks-in-string-to-minimize-its-value/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s. s[i] is either a lowercase English letter or '?'.
//
// For a string t having length m containing only lowercase English letters, we define the function cost(i) for an index i as the number of characters equal to t[i] that appeared before it, i.e. in the range [0, i - 1].
//
// The value of t is the sum of cost(i) for all indices i.
//
// For example, for the string t = "aab":
//
//
// 	cost(0) = 0
// 	cost(1) = 1
// 	cost(2) = 0
// 	Hence, the value of "aab" is 0 + 1 + 0 = 1.
//
//
// Your task is to replace all occurrences of '?' in s with any lowercase English letter so that the value of s is minimized.
//
// Return a string denoting the modified string with replaced occurrences of '?'. If there are multiple strings resulting in the minimum value, return the lexicographically smallest one.
//
// Example:
// Input:   s = "???" 
//
// Output:   "abc" 
//
// Explanation:  In this example, we can replace the occurrences of '?' to make s equal to "abc".
//
// For "abc", cost(0) = 0, cost(1) = 0, and cost(2) = 0.
//
// The value of "abc" is 0.
//
// Some other modifications of s that have a value of 0 are "cba", "abz", and, "hey".
//
// Among all of them, we choose the lexicographically smallest.
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either a lowercase English letter or '?'.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Suffix array (array, tree, string, suffix-array, tree-dp, lca)
//   • When to use: Use when needing to perform fast substring searches, pattern matching, or other string operations on a fixed text, especially when space efficiency is critical compared to suffix trees.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing only their starting indices. It is often paired with an LCP (Longest Common Prefix) array to enable efficient string algorithms, typically achieving O(N log N) or O(N) construction and O(M + log N) or O(M) search complexity.
//   • Invariants: The suffix array `A` stores indices such that `S[A[i]:]` is lexicographically smaller than `S[A[i+1]:]` for all valid `i`.; The `lcp[i]` value represents the length of the longest common prefix between `S[A[i-1]:]` and `S[A[i]:]`.
//   • Tips: Pair with an LCP array to significantly speed up pattern searching and other string queries.; Consider Enhanced Suffix Arrays (ESA) for improved space and time efficiency over suffix trees, especially for large datasets.
//   • Pitfalls: Naive pattern searching without LCP information can be O(M log N), which might be too slow for long patterns.; Construction can be complex to implement efficiently in linear time.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String minimizeStringValue(String s) {
        char[] chars = s.toCharArray();
        int n = chars.length;
        for (int i = 0; i < n; i++) {
            if (chars[i] == '?') {
                for (char c = 'a'; c <= 'z'; c++) {
                    if ((i > 0 && chars[i - 1] == c) || (i < n - 1 && chars[i + 1] == c)) {
                        continue;
                    }
                    chars[i] = c;
                    break;
                }
            }
        }
        return new String(chars);           
    }
}
