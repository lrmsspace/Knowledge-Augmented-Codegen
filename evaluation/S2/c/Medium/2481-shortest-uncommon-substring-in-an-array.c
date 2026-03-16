// Source: https://leetcode.com/problems/shortest-uncommon-substring-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array arr of size n consisting of non-empty strings.
//
// Find a string array answer of size n such that:
//
//
// 	answer[i] is the shortest substring of arr[i] that does not occur as a substring in any other string in arr. If multiple such substrings exist, answer[i] should be the lexicographically smallest. And if no such substring exists, answer[i] should be an empty string.
//
//
// Return the array answer.
//
// Example:
// Input: arr = ["cab","ad","bad","c"]
// Output: ["ab","","ba",""]
// Explanation: We have the following:
// - For the string "cab", the shortest substring that does not occur in any other string is either "ca" or "ab", we choose the lexicographically smaller substring, which is "ab".
// - For the string "ad", there is no substring that does not occur in any other string.
// - For the string "bad", the shortest substring that does not occur in any other string is "ba".
// - For the string "c", there is no substring that does not occur in any other string.
//
// Constraints:
// n == arr.length
// 	2 <= n <= 100
// 	1 <= arr[i].length <= 20
// 	arr[i] consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Suffix array (array, string, suffix-array, binary-search)
//   • When to use: Use suffix arrays for efficient string processing tasks like finding all occurrences of a pattern, locating the longest common substring, or performing various substring queries. It provides a sorted index of all suffixes.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices in lexicographical order. It enables various string operations to be performed efficiently, often with O(N log N) or O(N) time complexity for construction and O(M log N) or O(M) for queries.
//   • Invariants: The suffix array A always contains N elements, where N is the length of the original string.; For any valid index i, A[i] stores a starting position within the original string S.
//   • Tips: Append a unique sentinel character (e.g., '$') to the string to ensure all suffixes are distinct.; Combine with a Longest Common Prefix (LCP) array for enhanced functionality, such as counting distinct substrings.
//   • Pitfalls: Naive construction by sorting all suffixes directly is inefficient (O(N^2 log N) or worse).; Implementing advanced construction algorithms from scratch can be complex and error-prone.
// - Aho-Corasick algorithm (trie, array, trie-match)
//   • When to use: Use when you need to find all occurrences of a fixed set of multiple patterns within a larger text efficiently. It's particularly effective when patterns can overlap or share prefixes.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a set of patterns using a trie and failure links, enabling efficient simultaneous search for all patterns in a text. It achieves a time complexity of O(N + M + K).
//   • Invariants: Every path from the root to a node in the trie represents a unique prefix of at least one pattern.; After processing a character, the current automaton state corresponds to the longest suffix of the processed text that is also a prefix of some pattern.
//   • Tips: Construct the trie from all patterns first, then compute failure links.; Compute failure links using a BFS-like traversal from the root.
//   • Pitfalls: Incorrectly computing failure links, especially for nodes at depth 1 or for non-existent transitions.; Failing to implement output links, leading to missed matches for patterns that are suffixes of others.
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
//   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
//   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
//   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
//   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** shortestSubstrings(char** arr, int arrSize, int* returnSize) {
    *returnSize = arrSize;
    char** answer = (char**)malloc(arrSize * sizeof(char*));
    for (int i = 0; i < arrSize; i++) {
        answer[i] = (char*)malloc(21 * sizeof(char)); // Max length of substring is 20 + null terminator
        answer[i][0] = '\0'; // Initialize with empty string
    }

    for (int i = 0; i < arrSize; i++) {
        int len = strlen(arr[i]);
        int found = 0;

        for (int subLen = 1; subLen <= len && !found; subLen++) {
            for (int start = 0; start <= len - subLen && !found; start++) {
                char substring[21];
                strncpy(substring, arr[i] + start, subLen);
                substring[subLen] = '\0';

                int occursElsewhere = 0;
                for (int j = 0; j < arrSize; j++) {
                    if (j != i && strstr(arr[j], substring) != NULL) {
                        occursElsewhere = 1;
                        break;
                    }
                }

                if (!occursElsewhere) {
                    if (answer[i][0] == '\0' || strcmp(substring, answer[i]) < 0) {
                        strcpy(answer[i], substring);
                    }
                    found = 1;
                }
            }
        }
    }

    return answer;      
}
