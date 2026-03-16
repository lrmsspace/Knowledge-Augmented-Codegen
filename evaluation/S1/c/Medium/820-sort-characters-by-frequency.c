// Source: https://leetcode.com/problems/sort-characters-by-frequency/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string.
//
// Return the sorted string. If there are multiple answers, return any of them.
//
// Example:
// Input: s = "tree"
// Output: "eert"
// Explanation: 'e' appears twice while 'r' and 't' both appear once.
// So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
//
// Constraints:
// 1 <= s.length <= 5 * 105
// 	s consists of uppercase and lowercase English letters and digits.
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
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* frequencySort(char* s) {
    // Frequency array for all ASCII characters
    int freq[128] = {0};
    
    // Calculate frequency of each character in the string
    for (char* p = s; *p != '\0'; p++) {
        freq[(int)(*p)]++;
    }
    
    // Create an array of buckets where index represents frequency
    int maxFreq = 0;
    for (int i = 0; i < 128; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
        }
    }
    
    // Buckets to hold characters by their frequency
    char** buckets = (char**)malloc((maxFreq + 1) * sizeof(char*));
    for (int i = 0; i <= maxFreq; i++) {
        buckets[i] = NULL;
    }
    
    // Fill the buckets
    for (int i = 0; i < 128; i++) {
        if (freq[i] > 0) {
            if (buckets[freq[i]] == NULL) {
                buckets[freq[i]] = (char*)malloc(128 * sizeof(char));
                buckets[freq[i]][0] = '\0';
            }
            int len = strlen(buckets[freq[i]]);
            buckets[freq[i]][len] = (char)i;
            buckets[freq[i]][len + 1] = '\0';
        }
    }
    
    // Build the result string
    char* result = (char*)malloc((strlen(s) + 1) * sizeof(char));
    result[0] = '\0';
    
    for (int i = maxFreq; i > 0; i--) {
        if (buckets[i] != NULL) {
            for (char* p = buckets[i]; *p != '\0'; p++) {
                for (int j = 0; j < i; j++) {
                    strncat(result, p, 1);
                }
            }
            free(buckets[i]);
        }
    }
    
    free(buckets);
    
    return result;      
}
