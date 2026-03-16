// Source: https://leetcode.com/problems/longest-common-suffix-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays of strings wordsContainer and wordsQuery.
//
// For each wordsQuery[i], you need to find a string from wordsContainer that has the longest common suffix with wordsQuery[i]. If there are two or more strings in wordsContainer that share the longest common suffix, find the string that is the smallest in length. If there are two or more such strings that have the same smallest length, find the one that occurred earlier in wordsContainer.
//
// Return an array of integers ans, where ans[i] is the index of the string in wordsContainer that has the longest common suffix with wordsQuery[i].
//
// Example:
// Input: wordsContainer = ["abcd","bcd","xbcd"], wordsQuery = ["cd","bcd","xyz"]
//
// Output: [1,1,1]
//
// Explanation:
//
// Let's look at each wordsQuery[i] separately:
//
//
// 	For wordsQuery[0] = "cd", strings from wordsContainer that share the longest common suffix "cd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// 	For wordsQuery[1] = "bcd", strings from wordsContainer that share the longest common suffix "bcd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// 	For wordsQuery[2] = "xyz", there is no string from wordsContainer that shares a common suffix. Hence the longest common suffix is "", that is shared with strings at index 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
//
// Constraints:
// 1 <= wordsContainer.length, wordsQuery.length <= 104
// 	1 <= wordsContainer[i].length <= 5 * 103
// 	1 <= wordsQuery[i].length <= 5 * 103
// 	wordsContainer[i] consists only of lowercase English letters.
// 	wordsQuery[i] consists only of lowercase English letters.
// 	Sum of wordsContainer[i].length is at most 5 * 105.
// 	Sum of wordsQuery[i].length is at most 5 * 105.
//
// Helpful references (internal KB):
// - Suffix Array (string, array, merge-sort)
//   • When to use: Use when needing to efficiently query properties of all suffixes or substrings of a given text, especially for pattern matching or finding repeated structures. It is particularly useful for problems requiring lexicographical ordering of all suffixes.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices. It enables efficient string operations like pattern searching and finding longest common prefixes, typically constructed in O(N log N) time.
//   • Invariants: After k iterations, suffixes are sorted correctly up to a certain length (e.g., 2^k).; All suffixes of the original string are represented by their starting indices in the array.
//   • Tips: Append a unique sentinel character (e.g., '$') smaller than any other character to the string.; Utilize the LCP array, often built alongside, for advanced string queries and optimizations.
//   • Pitfalls: Naive sorting of suffixes by string comparison leads to an inefficient O(N^2 log N) complexity.; High memory usage for very long strings due to storing all suffixes implicitly or explicitly.
// - Tries (trie, tree, trie-match)
//   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
//   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
//   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
// - Longest increasing subsequence (array, greedy, dp-1d)
//   • When to use: Use when finding the longest sequence of elements in a given array such that each element is greater than the preceding one, without changing their relative order. It's applicable for optimizing problems involving ordered subsets.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of an array where elements are in strictly increasing order. It can be solved in O(N log N) time using a greedy approach with binary search, or O(N^2) using dynamic programming.
//   • Invariants: The 'tails' array elements are always in strictly increasing order.; tails[i] stores the smallest possible ending element of an increasing subsequence of length i+1.
//   • Tips: Prefer the O(N log N) greedy approach with binary search for better performance.; The 'tails' array in the greedy approach stores the smallest tail of all increasing subsequences of a certain length.
//   • Pitfalls: Confusing LIS with Longest Common Subsequence (LCS) or contiguous subarrays.; Incorrectly handling duplicate elements when 'strictly increasing' is required.
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
int* stringIndices(char** wordsContainer, int wordsContainerSize, char** wordsQuery, int wordsQuerySize, int* returnSize) {
    // Trie node structure
    typedef struct TrieNode {
        struct TrieNode* children[26];
        int index; // Index of the word in wordsContainer
        int length; // Length of the word
    } TrieNode;

    // Create a new trie node
    TrieNode* createNode() {
        TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
        for (int i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
        node->index = -1;
        node->length = 0;
        return node;
    }

    // Insert a word into the trie in reversed order
    void insert(TrieNode* root, const char* word, int index) {
        TrieNode* curr = root;
        int len = strlen(word);
        for (int i = len - 1; i >= 0; i--) {
            int ch = word[i] - 'a';
            if (!curr->children[ch]) {
                curr->children[ch] = createNode();
            }
            curr = curr->children[ch];
        }
        // Update index and length if it's the first insertion or shorter length
        if (curr->index == -1 || len < curr->length) {
            curr->index = index;
            curr->length = len;
        }
    }

    // Search for the longest common suffix in the trie
    int search(TrieNode* root, const char* word) {
        TrieNode* curr = root;
        int len = strlen(word);
        int resultIndex = -1;
        for (int i = len - 1; i >= 0; i--) {
            int ch = word[i] - 'a';
            if (!curr->children[ch]) {
                break;
            }
            curr = curr->children[ch];
            if (curr->index != -1) {
                resultIndex = curr->index;
            }
        }
        return resultIndex;
    }

    // Build the trie from wordsContainer
    TrieNode* root = createNode();
    for (int i = 0; i < wordsContainerSize; i++) {
        insert(root, wordsContainer[i], i);
    }

    // Prepare the result array
    int* result = (int*)malloc(wordsQuerySize * sizeof(int));
    for (int i = 0; i < wordsQuerySize; i++) {
        result[i] = search(root, wordsQuery[i]);
    }
    *returnSize = wordsQuerySize;
    return result;
}
