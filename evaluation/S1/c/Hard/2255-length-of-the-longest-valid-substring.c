// Source: https://leetcode.com/problems/length-of-the-longest-valid-substring/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string word and an array of strings forbidden.
//
// A string is called valid if none of its substrings are present in forbidden.
//
// Return the length of the longest valid substring of the string word.
//
// A substring is a contiguous sequence of characters in a string, possibly empty.
//
// Example:
// Input: word = "cbaaaabc", forbidden = ["aaa","cb"]
// Output: 4
// Explanation: There are 11 valid substrings in word: "c", "b", "a", "ba", "aa", "bc", "baa", "aab", "ab", "abc" and "aabc". The length of the longest valid substring is 4. 
// It can be shown that all other substrings contain either "aaa" or "cb" as a substring.
//
// Constraints:
// 1 <= word.length <= 105
// 	word consists only of lowercase English letters.
// 	1 <= forbidden.length <= 105
// 	1 <= forbidden[i].length <= 10
// 	forbidden[i] consists only of lowercase English letters.
//
// Helpful references (internal KB):
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
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int longestValidSubstring(char* word, char** forbidden, int forbiddenSize) {
    /* Build forbidden set using a hash map */
    enum { HASH_SIZE = 131071 };
    typedef struct HashEntry {
        char *str;
        struct HashEntry *next;
    } HashEntry;
    HashEntry *hashMap[HASH_SIZE];
    memset(hashMap, 0, sizeof(hashMap));

    unsigned long hashFunc(const char *s) {
        unsigned long hash = 5381;
        int c;
        while ((c = *s++)) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % HASH_SIZE;
    }

    for (int i = 0; i < forbiddenSize; i++) {
        unsigned long h = hashFunc(forbidden[i]);
        HashEntry *entry = (HashEntry*)malloc(sizeof(HashEntry));
        entry->str = forbidden[i];
        entry->next = hashMap[h];
        hashMap[h] = entry;
    }

    int maxLen = 0;
    int n = strlen(word);
    for (int end = 0, start = 0; end < n; end++) {
        for (int len = 1; len <= 10 && end - len + 1 >= start; len++) {
            char temp = word[end - len + 1 + len]; // save next char
            word[end - len + 1 + len] = '\0'; // temporarily terminate
            unsigned long h = hashFunc(&word[end - len + 1]);
            HashEntry *entry = hashMap[h];
            int found = 0;
            while (entry) {
                if (strcmp(entry->str, &word[end - len + 1]) == 0) {
                    found = 1;
                    break;
                }
                entry = entry->next;
            }
            word[end - len + 1 + len] = temp; // restore char
            if (found) {
                start = end - len + 2; // move start forward
                break;
            }
        }
        if (end - start + 1 > maxLen) {
            maxLen = end - start + 1;
        }
    }

    /* Free hash map */
    for (int i = 0; i < HASH_SIZE; i++) {
        HashEntry *entry = hashMap[i];
        while (entry) {
            HashEntry *temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
    return maxLen;
}
