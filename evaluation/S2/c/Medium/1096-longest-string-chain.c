// Source: https://leetcode.com/problems/longest-string-chain/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of words where each word consists of lowercase English letters.
//
// wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB.
//
//
// 	For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
//
//
// A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain with k == 1.
//
// Return the length of the longest possible word chain with words chosen from the given list of words.
//
// Example:
// Input: words = ["a","b","ba","bca","bda","bdca"]
// Output: 4
// Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 16
// 	words[i] only consists of lowercase English letters.
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
// - Suffix array (array, tree, string, suffix-array, tree-dp, lca)
//   • When to use: Use when needing to perform fast substring searches, pattern matching, or other string operations on a fixed text, especially when space efficiency is critical compared to suffix trees.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing only their starting indices. It is often paired with an LCP (Longest Common Prefix) array to enable efficient string algorithms, typically achieving O(N log N) or O(N) construction and O(M + log N) or O(M) search complexity.
//   • Invariants: The suffix array `A` stores indices such that `S[A[i]:]` is lexicographically smaller than `S[A[i+1]:]` for all valid `i`.; The `lcp[i]` value represents the length of the longest common prefix between `S[A[i-1]:]` and `S[A[i]:]`.
//   • Tips: Pair with an LCP array to significantly speed up pattern searching and other string queries.; Consider Enhanced Suffix Arrays (ESA) for improved space and time efficiency over suffix trees, especially for large datasets.
//   • Pitfalls: Naive pattern searching without LCP information can be O(M log N), which might be too slow for long patterns.; Construction can be complex to implement efficiently in linear time.
// - Aho-Corasick algorithm (trie, graph, bfs, trie-match)
//   • When to use: Use this algorithm to efficiently find all occurrences of a fixed set of patterns within a larger text. It is ideal for scenarios requiring simultaneous searching for multiple dictionary words.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a set of patterns, allowing linear time searching for all pattern occurrences in a text. It extends a trie with suffix links and failure transitions for efficient traversal, achieving O(N + M + K) complexity where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: All nodes at depth 'd' have their suffix links correctly computed before processing nodes at depth 'd+1'.; For any node 'u', its suffix link points to the longest proper suffix of the string represented by 'u' that is also a prefix of some pattern.
//   • Tips: Build the trie from all patterns first, marking nodes that represent the end of a pattern.; Compute suffix links using a breadth-first search (BFS) starting from the root.
//   • Pitfalls: Incorrectly computing suffix links can lead to wrong matches or infinite loops.; High memory usage can occur for large alphabets or a vast number of patterns.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int longestStrChain(char** words, int wordsSize) {
    // Sort the words by their lengths
    qsort(words, wordsSize, sizeof(char*), [](const void* a, const void* b) {
        return strlen(*(char**)a) - strlen(*(char**)b);
    });

    int longestChain[wordsSize];
    int maxLength = 1;

    for (int i = 0; i < wordsSize; i++) {
        longestChain[i] = 1; // Every word is a chain of length 1 by itself
        for (int j = 0; j < i; j++) {
            if (strlen(words[i]) == strlen(words[j]) + 1 && isPredecessor(words[j], words[i])) {
                longestChain[i] = longestChain[j] + 1;
                maxLength = max(maxLength, longestChain[i]);
            }
        }
    }

    return maxLength;       
}
