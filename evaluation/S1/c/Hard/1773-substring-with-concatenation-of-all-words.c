// Source: https://leetcode.com/problems/substring-with-concatenation-of-all-words/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an array of strings words. All the strings of words are of the same length.
//
// A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.
//
//
// 	For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated string because it is not the concatenation of any permutation of words.
//
//
// Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.
//
// Example:
// Input: s = "barfoothefoobarman", words = ["foo","bar"]
//
// Output: [0,9]
//
// Explanation:
//
// The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
// The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.
//
// Constraints:
// 1 <= s.length <= 104
// 	1 <= words.length <= 5000
// 	1 <= words[i].length <= 30
// 	s and words[i] consist of lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Aho-Corasick Algorithm for Pattern Searching (string, array, aho-corasick, enumeration)
//   • When to use: Use when you need to find all occurrences of a fixed set of patterns (a dictionary) within a larger text efficiently. It is particularly effective for scenarios with many patterns or long texts where patterns might overlap.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses this automaton to search for all pattern occurrences in a text in a single pass. It achieves a time complexity of O(N + M + K) where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: The trie structure correctly represents all prefixes of all patterns in the dictionary.; Each node's failure link points to the longest proper suffix of the string ending at that node which is also a prefix in the trie.
//   • Tips: Build the trie first from all patterns, marking terminal nodes.; Compute failure links using a BFS-like approach, similar to KMP's LPS array.
//   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to handle output links (dictionary links) will miss patterns found via failure transitions.
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
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    if (wordsSize == 0 || s == NULL || *s == '\0') {
        *returnSize = 0;
        return NULL;
    }

    int wordLen = strlen(words[0]);
    int substringLen = wordLen * wordsSize;
    int sLen = strlen(s);
    int* result = (int*)malloc(sLen * sizeof(int));
    *returnSize = 0;

    // Build the frequency map for words
    #define HASH_MAP_SIZE 100003
    typedef struct WordCount {
        char* word;
        int count;
        struct WordCount* next;
    } WordCount;

    WordCount* hashMap[HASH_MAP_SIZE] = {0};

    unsigned long long hashString(const char* str) {
        unsigned long long hash = 5381;
        int c;
        while ((c = *str++)) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % HASH_MAP_SIZE;
    }

    for (int i = 0; i < wordsSize; i++) {
        unsigned long long hashIndex = hashString(words[i]);
        WordCount* entry = hashMap[hashIndex];
        while (entry && strcmp(entry->word, words[i]) != 0) {
            hashIndex = (hashIndex + 1) % HASH_MAP_SIZE;
            entry = hashMap[hashIndex];
        }
        if (!entry) {
            entry = (WordCount*)malloc(sizeof(WordCount));
            entry->word = words[i];
            entry->count = 0;
            entry->next = NULL;
            hashMap[hashIndex] = entry;
        }
        entry->count++;
    }

    // Check each substring in s
    for (int i = 0; i <= sLen - substringLen; i++) {
        int found = 1;
        WordCount* tempMap[HASH_MAP_SIZE] = {0};

        for (int j = 0; j < wordsSize; j++) {
            char* subStr = strndup(s + i + j * wordLen, wordLen);
            unsigned long long hashIndex = hashString(subStr);
            WordCount* entry = hashMap[hashIndex];
            while (entry && strcmp(entry->word, subStr) != 0) {
                hashIndex = (hashIndex + 1) % HASH_MAP_SIZE;
                entry = hashMap[hashIndex];
            }
            if (!entry) {
                found = 0;
                free(subStr);
                break;
            }

            // Update tempMap
            WordCount* tempEntry = tempMap[hashIndex];
            while (tempEntry && strcmp(tempEntry->word, subStr) != 0) {
                hashIndex = (hashIndex + 1) % HASH_MAP_SIZE;
                tempEntry = tempMap[hashIndex];
            }
            if (!tempEntry) {
                tempEntry = (WordCount*)malloc(sizeof(WordCount));
                tempEntry->word = subStr;
                tempEntry->count = 0;
                tempEntry->next = NULL;
                tempMap[hashIndex] = tempEntry;
            }
            tempEntry->count++;
            if (tempEntry->count > entry->count) {
                found = 0;
                free(subStr);
                break;
            }
            free(subStr);
        }

        if (found) {
            result[*returnSize] = i;
            (*returnSize)++;
        }

        // Free tempMap
        for (int k = 0; k < HASH_MAP_SIZE; k++) {
            WordCount* tempEntry = tempMap[k];
            while (tempEntry) {
                WordCount* toFree = tempEntry;
                tempEntry = tempEntry->next;
                free(toFree);
            }
        }
    }
    // Free hashMap
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        WordCount* entry = hashMap[i];
        while (entry) {
            WordCount* toFree = entry;
            entry = entry->next;
            free(toFree);
        }
    }
    return result;
}
