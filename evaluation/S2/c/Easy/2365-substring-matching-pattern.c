// Source: https://leetcode.com/problems/substring-matching-pattern/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s and a pattern string p, where p contains exactly one '*' character.
//
// The '*' in p can be replaced with any sequence of zero or more characters.
//
// Return true if p can be made a substring of s, and false otherwise.
//
// Example:
// Input: s = "leetcode", p = "ee*e"
//
// Output: true
//
// Explanation:
//
// By replacing the '*' with "tcod", the substring "eetcode" matches the pattern.
//
// Constraints:
// 1 <= s.length <= 50
// 	1 <= p.length <= 50 
// 	s contains only lowercase English letters.
// 	p contains only lowercase English letters and exactly one '*'
//
// Helpful references (internal KB):
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Tries (trie, array, trie-match)
//   • When to use: Use when managing string keys in a symbol table and needing efficient prefix, wildcard, or longest prefix matching operations, offering flexibility beyond binary search trees and speed comparable to hashing.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set or associative array where keys are typically strings. It allows for efficient retrieval of keys based on their prefixes, achieving O(L) time complexity for operations, where L is the key length.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node exists only if it is part of at least one stored key.
//   • Tips: Choose an appropriate branching factor (R) based on the alphabet size.; Represent children using arrays for fixed alphabets or hash maps for sparse ones.
//   • Pitfalls: High memory consumption for large alphabets or sparse data.; Deletion of keys can be complex, requiring careful handling of empty branches.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool hasMatch(char* s, char* p) {
    int sLen = strlen(s), pLen = strlen(p);
    int starIdx = -1, sIdx = 0, pIdx = 0;

    while (sIdx < sLen) {
        if (pIdx < pLen && (p[pIdx] == s[sIdx] || p[pIdx] == '*')) {
            if (p[pIdx] == '*') {
                starIdx = pIdx;
                pIdx++;
            } else {
                sIdx++;
                pIdx++;
            }
        } else if (starIdx != -1) {
            pIdx = starIdx + 1;
            sIdx++;
        } else {
            return false;
        }
    }

    while (pIdx < pLen && p[pIdx] == '*') {
        pIdx++;
    }

    return pIdx == pLen;        
}
