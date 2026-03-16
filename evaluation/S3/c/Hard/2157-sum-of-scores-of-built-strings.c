// Source: https://leetcode.com/problems/sum-of-scores-of-built-strings/   |   Difficulty: Hard
//
// Problem Description:
// You are building a string s of length n one character at a time, prepending each new character to the front of the string. The strings are labeled from 1 to n, where the string with length i is labeled si.
//
//
// 	For example, for s = "abaca", s1 == "a", s2 == "ca", s3 == "aca", etc.
//
//
// The score of si is the length of the longest common prefix between si and sn (Note that s == sn).
//
// Given the final string s, return the sum of the score of every si.
//
// Example:
// Input: s = "babab"
// Output: 9
// Explanation:
// For s1 == "b", the longest common prefix is "b" which has a score of 1.
// For s2 == "ab", there is no common prefix so the score is 0.
// For s3 == "bab", the longest common prefix is "bab" which has a score of 3.
// For s4 == "abab", there is no common prefix so the score is 0.
// For s5 == "babab", the longest common prefix is "babab" which has a score of 5.
// The sum of the scores is 1 + 0 + 3 + 0 + 5 = 9, so we return 9.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
//
// Helpful references (internal KB):
// - Z-function and its calculation (string, array, counting)
//   • When to use: Use when you need to find all occurrences of a pattern within a text, or to identify repeated prefixes within a string efficiently.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the string and its suffix starting at index i. It runs in linear time, O(N), where N is the length of the string.
//   • Invariants: For all j < i, z[j] correctly stores the length of the longest common prefix between S and S[j...].; The segment [l, r-1] represents the rightmost segment that is a prefix of S and has been fully processed.
//   • Tips: Initialize z[0] to 0 (or N, depending on definition) and handle it as a base case.; Utilize previously computed Z-values to avoid redundant comparisons, especially within the 'rightmost matching segment' [l, r].
//   • Pitfalls: Incorrectly updating or using the 'rightmost matching segment' boundaries (l and r).; Off-by-one errors when calculating indices or lengths, especially with 0-based vs. 1-based indexing.
// - Z-function and its calculation (string, array, two-pointers)
//   • When to use: Use when you need to find the length of the longest common prefix between a string and all its suffixes efficiently. It is fundamental for various string matching and pattern searching problems.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the original string and its suffix starting at index i. This algorithm calculates the entire Z-array in O(N) time complexity.
//   • Invariants: For all k < i, z[k] has been correctly computed.; The interval [l, r) always represents the rightmost segment match found so far.
//   • Tips: Leverage previously computed Z-values to avoid redundant comparisons.; Maintain a [l, r) window representing the rightmost segment match found so far.
//   • Pitfalls: Incorrectly handling the base case z[0] (usually set to 0).; Off-by-one errors when calculating the length of the prefix or updating the window.
// - Suffix array (array, tree, string, suffix-array, tree-dp, lca)
//   • When to use: Use when needing to perform fast substring searches, pattern matching, or other string operations on a fixed text, especially when space efficiency is critical compared to suffix trees.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing only their starting indices. It is often paired with an LCP (Longest Common Prefix) array to enable efficient string algorithms, typically achieving O(N log N) or O(N) construction and O(M + log N) or O(M) search complexity.
//   • Invariants: The suffix array `A` stores indices such that `S[A[i]:]` is lexicographically smaller than `S[A[i+1]:]` for all valid `i`.; The `lcp[i]` value represents the length of the longest common prefix between `S[A[i-1]:]` and `S[A[i]:]`.
//   • Tips: Pair with an LCP array to significantly speed up pattern searching and other string queries.; Consider Enhanced Suffix Arrays (ESA) for improved space and time efficiency over suffix trees, especially for large datasets.
//   • Pitfalls: Naive pattern searching without LCP information can be O(M log N), which might be too slow for long patterns.; Construction can be complex to implement efficiently in linear time.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long sumScores(char* s) {
    int n = strlen(s);
    long long sum = 0;
    int* z = (int*)malloc(n * sizeof(int));
    z[0] = 0; // Z[0] is typically defined as 0 for the Z-function

    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r) {
            z[i] = (r - i < z[i - l]) ? r - i : z[i - l];
        } else {
            z[i] = 0;
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
        sum += z[i];
    }
    sum += n; // Add the score of s itself, which is n
    free(z);
    return sum;     
}
