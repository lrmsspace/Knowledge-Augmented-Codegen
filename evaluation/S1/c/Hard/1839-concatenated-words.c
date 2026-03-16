// Source: https://leetcode.com/problems/concatenated-words/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
//
// A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.
//
// Example:
// Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
// Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
// Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
// "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
// "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
//
// Constraints:
// 1 <= words.length <= 104
// 	1 <= words[i].length <= 30
// 	words[i] consists of only lowercase English letters.
// 	All the strings of words are unique.
// 	1 <= sum(words[i].length) <= 105
//
// Helpful references (internal KB):
// - Tries (trie, tree, trie-match)
//   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
//   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
//   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Suffix Array (string, array, counting-sort, radix-sort)
//   • When to use: Use when you need to efficiently query or analyze all suffixes of a string, often for pattern matching, string searching, or finding repeated substrings. It provides a sorted order of all suffixes.
//   • Idea: The Suffix Array algorithm constructs an array containing the starting indices of all suffixes of a string, sorted lexicographically. It typically uses a doubling strategy with counting sort or radix sort in each step, achieving an O(N log N) time complexity.
//   • Invariants: After iteration k, p contains the sorted indices of all cyclic substrings of length 2^k.; After iteration k, c[i] represents the equivalence class of the cyclic substring starting at i with length 2^k.
//   • Tips: Append a unique, smallest character (e.g., '$') to the string to handle suffixes as cyclic shifts.; Utilize counting sort for efficient sorting of characters and pairs of equivalence classes.
//   • Pitfalls: Incorrectly handling the sentinel character can lead to incorrect suffix order or out-of-bounds access.; Off-by-one errors when calculating indices for cyclic shifts or substring lengths.
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
char** findAllConcatenatedWordsInADict(char** words, int wordsSize, int* returnSize) {
    // Trie node structure
    typedef struct TrieNode {
        struct TrieNode* children[26];
        int isEnd;
    } TrieNode;

    // Create a new trie node
    TrieNode* createNode() {
        TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
        for (int i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
        node->isEnd = 0;
        return node;
    }

    // Insert a word into the trie
    void insert(TrieNode* root, const char* word) {
        TrieNode* curr = root;
        while (*word) {
            int index = *word - 'a';
            if (!curr->children[index]) {
                curr->children[index] = createNode();
            }
            curr = curr->children[index];
            word++;
        }
        curr->isEnd = 1;
    }

    // Check if the word can be formed by concatenating other words in the trie
    int canForm(TrieNode* root, const char* word, int count) {
        if (*word == '\0') {
            return count >= 2;
        }
        TrieNode* curr = root;
        for (const char* p = word; *p; p++) {
            int index = *p - 'a';
            if (!curr->children[index]) {
                return 0;
            }
            curr = curr->children[index];
            if (curr->isEnd) {
                if (canForm(root, p + 1, count + 1)) {
                    return 1;
                }
            }
        }
        return 0;
    }

    // Main logic
    TrieNode* root = createNode();
    for (int i = 0; i < wordsSize; i++) {
        insert(root, words[i]);
    }

    char** result = (char**)malloc(wordsSize * sizeof(char*));
    int resCount = 0;
    for (int i = 0; i < wordsSize; i++) {
        if (canForm(root, words[i], 0)) {
            result[resCount++] = words[i];
        }
    }

    *returnSize = resCount;
    return result;      
}
