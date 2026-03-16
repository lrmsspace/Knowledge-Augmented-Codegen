// Source: https://leetcode.com/problems/uncommon-words-from-two-sentences/   |   Difficulty: Easy
//
// Problem Description:
// A sentence is a string of single-space separated words where each word consists only of lowercase letters.
//
// A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.
//
// Given two sentences s1 and s2, return a list of all the uncommon words. You may return the answer in any order.
//
// Example:
// Input: s1 = "this apple is sweet", s2 = "this apple is sour"
//
// Output: ["sweet","sour"]
//
// Explanation:
//
// The word "sweet" appears only in s1, while the word "sour" appears only in s2.
//
// Constraints:
// 1 <= s1.length, s2.length <= 200
// 	s1 and s2 consist of lowercase English letters and spaces.
// 	s1 and s2 do not have leading or trailing spaces.
// 	All the words in s1 and s2 are separated by a single space.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
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
char** uncommonFromSentences(char* s1, char* s2, int* returnSize) {
    #define MAX_WORDS 100
    #define MAX_WORD_LEN 21

    char** result = (char**)malloc(MAX_WORDS * sizeof(char*));
    int count1[MAX_WORDS] = {0};
    int count2[MAX_WORDS] = {0};
    char words1[MAX_WORDS][MAX_WORD_LEN] = {{0}};
    char words2[MAX_WORDS][MAX_WORD_LEN] = {{0}};
    int wordCount1 = 0, wordCount2 = 0;

    // Helper function to split sentence into words and count occurrences
    void splitAndCount(char* s, char words[][MAX_WORD_LEN], int* counts, int* wordCount) {
        char* token = strtok(s, " ");
        while (token != NULL) {
            int found = 0;
            for (int i = 0; i < *wordCount; i++) {
                if (strcmp(words[i], token) == 0) {
                    counts[i]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(words[*wordCount], token);
                counts[*wordCount] = 1;
                (*wordCount)++;
            }
            token = strtok(NULL, " ");
        }
    }

    // Split and count words in both sentences
    splitAndCount(s1, words1, count1, &wordCount1);
    splitAndCount(s2, words2, count2, &wordCount2);

    // Find uncommon words
    int resultCount = 0;
    for (int i = 0; i < wordCount1; i++) {
        if (count1[i] == 1) {
            int foundInS2 = 0;
            for (int j = 0; j < wordCount2; j++) {
                if (strcmp(words1[i], words2[j]) == 0) {
                    foundInS2 = 1;
                    break;
                }
            }
            if (!foundInS2) {
                result[resultCount] = (char*)malloc((strlen(words1[i]) + 1) * sizeof(char));
                strcpy(result[resultCount], words1[i]);
                resultCount++;
            }
        }
    }

    for (int i = 0; i < wordCount2; i++) {
        if (count2[i] == 1) {
            int foundInS1 = 0;
            for (int j = 0; j < wordCount1; j++) {
                if (strcmp(words2[i], words1[j]) == 0) {
                    foundInS1 = 1;
                    break;
                }
            }
            if (!foundInS1) {
                result[resultCount] = (char*)malloc((strlen(words2[i]) + 1) * sizeof(char));
                strcpy(result[resultCount], words2[i]);
                resultCount++;
            }
        }
    }
    *returnSize = resultCount;
    return result;
}
