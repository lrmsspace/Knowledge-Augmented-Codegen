// Source: https://leetcode.com/problems/find-resultant-array-after-removing-anagrams/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed string array words, where words[i] consists of lowercase English letters.
//
// In one operation, select any index i such that 0 < i < words.length and words[i - 1] and words[i] are anagrams, and delete words[i] from words. Keep performing this operation as long as you can select an index that satisfies the conditions.
//
// Return words after performing all operations. It can be shown that selecting the indices for each operation in any arbitrary order will lead to the same result.
//
// An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase using all the original letters exactly once. For example, "dacb" is an anagram of "abdc".
//
// Example:
// Input: words = ["abba","baba","bbaa","cd","cd"]
// Output: ["abba","cd"]
// Explanation:
// One of the ways we can obtain the resultant array is by using the following operations:
// - Since words[2] = "bbaa" and words[1] = "baba" are anagrams, we choose index 2 and delete words[2].
//   Now words = ["abba","baba","cd","cd"].
// - Since words[1] = "baba" and words[0] = "abba" are anagrams, we choose index 1 and delete words[1].
//   Now words = ["abba","cd","cd"].
// - Since words[2] = "cd" and words[1] = "cd" are anagrams, we choose index 2 and delete words[2].
//   Now words = ["abba","cd"].
// We can no longer perform any operations, so ["abba","cd"] is the final answer.
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 10
// 	words[i] consists of lowercase English letters.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
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
char** removeAnagrams(char** words, int wordsSize, int* returnSize) {
    if (wordsSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    char** result = (char**)malloc(wordsSize * sizeof(char*));
    int count = 0;

    // Helper function to sort characters in a string
    void sortString(char* str) {
        int len = strlen(str);
        for (int i = 0; i < len - 1; i++) {
            for (int j = 0; j < len - i - 1; j++) {
                if (str[j] > str[j + 1]) {
                    char temp = str[j];
                    str[j] = str[j + 1];
                    str[j + 1] = temp;
                }
            }
        }
    }

    // Sort the first word and add it to the result
    char* prevSorted = strdup(words[0]);
    sortString(prevSorted);
    result[count++] = words[0];

    for (int i = 1; i < wordsSize; i++) {
        char* currentSorted = strdup(words[i]);
        sortString(currentSorted);

        if (strcmp(prevSorted, currentSorted) != 0) {
            result[count++] = words[i];
            free(prevSorted);
            prevSorted = currentSorted;
        } else {
            free(currentSorted);
        }
    }

    free(prevSorted);
    *returnSize = count;
    return result;      
}
