// Source: https://leetcode.com/problems/vowel-spellchecker/   |   Difficulty: Medium
//
// Problem Description:
// Given a wordlist, we want to implement a spellchecker that converts a query word into a correct word.
//
// For a given query word, the spell checker handles two categories of spelling mistakes:
//
//
// 	Capitalization: If the query matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the case in the wordlist.
//
// Example:
// wordlist = ["yellow"], query = "YellOw": correct = "yellow"
//
// Constraints:
// 1 <= wordlist.length, queries.length <= 5000
// 	1 <= wordlist[i].length, queries[i].length <= 7
// 	wordlist[i] and queries[i] consist only of only English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
//   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
//   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
//   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
//   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
// - Aho-Corasick Algorithm for Pattern Searching (string, trie, aho-corasick, simulation)
//   • When to use: Use when you need to find all occurrences of a fixed set of patterns within a larger text efficiently. It's particularly effective for scenarios involving many patterns and potential overlaps.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses it to find all occurrences of these patterns in a text in a single pass. It operates in O(N + M + K) time, where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: All patterns in the dictionary are correctly represented in the trie (goto function).; The failure link `f[u]` for any state `u` points to the state representing the longest proper suffix of the string corresponding to `u` that is also a prefix of some pattern.
//   • Tips: Build the trie (goto function) first from all patterns.; Construct failure links using a BFS-like approach to ensure correct shortest suffix matching.
//   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to propagate output matches through failure links can miss valid pattern occurrences.
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
char** spellchecker(char** wordlist, int wordlistSize, char** queries, int queriesSize, int* returnSize) {
    // Helper function to convert a word to lowercase
    char* toLowerCase(const char* word) {
        int len = strlen(word);
        char* lowerWord = (char*)malloc((len + 1) * sizeof(char));
        for (int i = 0; i < len; i++) {
            lowerWord[i] = tolower(word[i]);
        }
        lowerWord[len] = '\0';
        return lowerWord;
    }

    // Helper function to convert a word to its vowel-error form
    char* toVowelErrorForm(const char* word) {
        int len = strlen(word);
        char* vowelErrorWord = (char*)malloc((len + 1) * sizeof(char));
        for (int i = 0; i < len; i++) {
            char c = tolower(word[i]);
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vowelErrorWord[i] = '*'; // Replace vowels with '*'
            } else {
                vowelErrorWord[i] = c;
            }
        }
        vowelErrorWord[len] = '\0';
        return vowelErrorWord;
    }

    // Create hash maps for exact matches, case-insensitive matches, and vowel-error matches
    #define HASH_MAP_SIZE 10007 // A prime number for better distribution
    char* exactMatchMap[HASH_MAP_SIZE] = {0};
    char* caseInsensitiveMap[HASH_MAP_SIZE] = {0};
    char* vowelErrorMap[HASH_MAP_SIZE] = {0};

    for (int i = 0; i < wordlistSize; i++) {
        unsigned long hash = 5381;
        const char* word = wordlist[i];
        for (const char* p = word; *p; p++) {
            hash = ((hash << 5) + hash) + *p; // hash * 33 + c
        }
        hash %= HASH_MAP_SIZE;

        // Exact match
        if (!exactMatchMap[hash]) {
            exactMatchMap[hash] = word;
        }

        // Case-insensitive match
        char* lowerWord = toLowerCase(word);
        unsigned long caseHash = 5381;
        for (const char* p = lowerWord; *p; p++) {
            caseHash = ((caseHash << 5) + caseHash) + *p;
        }
        caseHash %= HASH_MAP_SIZE;
        if (!caseInsensitiveMap[caseHash]) {
            caseInsensitiveMap[caseHash] = word;
        }
        free(lowerWord);

        // Vowel-error match
        char* vowelErrorWord = toVowelErrorForm(word);
        unsigned long vowelHash = 5381;
        for (const char* p = vowelErrorWord; *p; p++) {
            vowelHash = ((vowelHash << 5) + vowelHash) + *p;
        }
        vowelHash %= HASH_MAP_SIZE;
        if (!vowelErrorMap[vowelHash]) {
            vowelErrorMap[vowelHash] = word;
        }
        free(vowelErrorWord);
    }
    // Process queries
    char** result = (char**)malloc(queriesSize * sizeof(char*));
    for (int i = 0; i < queriesSize; i++) {
        const char* query = queries[i];
        unsigned long hash = 5381;
        for (const char* p = query; *p; p++) {
            hash = ((hash << 5) + hash) + *p;
        }
        hash %= HASH_MAP_SIZE;

        // Check for exact match
        if (exactMatchMap[hash] && strcmp(exactMatchMap[hash], query) == 0) {
            result[i] = exactMatchMap[hash];
            continue;
        }

        // Check for case-insensitive match
        char* lowerQuery = toLowerCase(query);
        unsigned long caseHash = 5381;
        for (const char* p = lowerQuery; *p; p++) {
            caseHash = ((caseHash << 5) + caseHash) + *p;
        }
        caseHash %= HASH_MAP_SIZE;
        if (caseInsensitiveMap[caseHash]) {
            result[i] = caseInsensitiveMap[caseHash];
            free(lowerQuery);
            continue;
        }
        free(lowerQuery);

        // Check for vowel-error match
        char* vowelErrorQuery = toVowelErrorForm(query);
        unsigned long vowelHash = 5381;
        for (const char* p = vowelErrorQuery; *p; p++) {
            vowelHash = ((vowelHash << 5) + vowelHash) + *p;
        }
        vowelHash %= HASH_MAP_SIZE;
        if (vowelErrorMap[vowelHash]) {
            result[i] = vowelErrorMap[vowelHash];
            free(vowelErrorQuery);
            continue;
        }
        free(vowelErrorQuery);

        // No match found
        result[i] = "";
    }
    *returnSize = queriesSize;
    return result;    
}
