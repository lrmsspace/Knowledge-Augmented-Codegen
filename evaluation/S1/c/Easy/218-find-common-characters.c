// Source: https://leetcode.com/problems/find-common-characters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string array words, return an array of all characters that show up in all strings within the words (including duplicates). You may return the answer in any order.
//
// Example:
// Input: words = ["bella","label","roller"]
// Output: ["e","l","l"]
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 100
// 	words[i] consists of lowercase English letters.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Data Compression (tree, heap, greedy, recursion, counting)
//   • When to use: Use when you need to losslessly compress data by assigning shorter bit sequences to more frequent symbols, aiming for the shortest possible average code length. It is effective for data with non-uniform character distributions.
//   • Idea: Huffman coding is a greedy algorithm that constructs an optimal prefix code for a given set of symbols and their frequencies. It builds a binary tree (Huffman trie) by repeatedly merging the two nodes with the smallest frequencies, resulting in an encoding with O(N + K log K) time complexity, where N is input length and K is alphabet size.
//   • Invariants: The priority queue always contains valid Huffman nodes, each representing a subtree or a leaf character.; Every internal node in the Huffman tree has exactly two children, and its frequency is the sum of its children's frequencies.
//   • Tips: Use a min-priority queue to efficiently retrieve and combine the two lowest-frequency nodes.; Represent the Huffman tree explicitly to generate codes and for decoding.
//   • Pitfalls: The overhead of storing the Huffman tree or frequency table can negate compression benefits for small inputs.; Not truly optimal for all data types; it's a statistical compression method.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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
char** commonChars(char** words, int wordsSize, int* returnSize) {
    int minFreq[26];
    for (int i = 0; i < 26; i++) {
        minFreq[i] = 100; // Since max length of words[i] is 100
    }

    for (int w = 0; w < wordsSize; w++) {
        int freq[26] = {0};
        for (char* p = words[w]; *p != '\0'; p++) {
            freq[*p - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            if (freq[i] < minFreq[i]) {
                minFreq[i] = freq[i];
            }
        }
    }

    char** result = (char**)malloc(100 * sizeof(char*)); // Max possible size
    int idx = 0;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < minFreq[i]; j++) {
            result[idx] = (char*)malloc(2 * sizeof(char));
            result[idx][0] = 'a' + i;
            result[idx][1] = '\0';
            idx++;
        }
    }

    *returnSize = idx;
    return result;      
}
