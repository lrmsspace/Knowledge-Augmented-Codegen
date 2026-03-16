// Source: https://leetcode.com/problems/repeated-dna-sequences/   |   Difficulty: Medium
//
// Problem Description:
// The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.
//
//
// 	For example, "ACGAATTCCG" is a DNA sequence.
//
//
// When studying DNA, it is useful to identify repeated sequences within the DNA.
//
// Given a string s that represents a DNA sequence, return all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule. You may return the answer in any order.
//
// Example:
// Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
// Output: ["AAAAACCCCC","CCCCCAAAAA"]
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either 'A', 'C', 'G', or 'T'.
//
// Helpful references (internal KB):
// - Substring Search (string, number, hashing, randomized, rolling-hash)
//   • When to use: Use when efficiently finding occurrences of a pattern string within a larger text string, especially for average-case fast string matching. It is suitable for scenarios involving large texts or multiple patterns.
//   • Idea: The Rabin-Karp algorithm finds pattern occurrences in a text by comparing hash values of the pattern and text substrings. It uses a rolling hash function for O(1) substring hash updates, achieving O(N+M) average time complexity and O(NM) worst-case.
//   • Invariants: The pattern's hash value patHash remains constant throughout the search.; At each step i, txtHash accurately represents the hash of txt[i...i+m-1].
//   • Tips: Choose a large prime modulus to minimize hash collisions.; Use a random base for polynomial hashing to enhance collision resistance.
//   • Pitfalls: Hash collisions can lead to false positives, increasing worst-case time.; Improper choice of prime modulus or base can degrade performance.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
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
char** findRepeatedDnaSequences(char* s, int* returnSize) {
    // Hash map to store counts of substrings
    #define HASH_MAP_SIZE 1048576  // 2^20
    typedef struct Node {
        char* substring;
        int count;
        struct Node* next;
    } Node;

    Node* hashMap[HASH_MAP_SIZE] = {0};

    // Function to compute hash value for a substring
    unsigned int hash(const char* str) {
        unsigned int h = 0;
        for (int i = 0; i < 10; i++) {
            h = (h << 2) | (str[i] & 3);  // Using only last 2 bits for A, C, G, T
        }
        return h % HASH_MAP_SIZE;
    }

    // Insert substring into hash map
    void insert(const char* str) {
        unsigned int h = hash(str);
        Node* node = hashMap[h];
        while (node) {
            if (strncmp(node->substring, str, 10) == 0) {
                node->count++;
                return;
            }
            node = node->next;
        }
        // Not found, create new node
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->substring = (char*)malloc(11 * sizeof(char));
        strncpy(newNode->substring, str, 10);
        newNode->substring[10] = '\0';
        newNode->count = 1;
        newNode->next = hashMap[h];
        hashMap[h] = newNode;
    }

    // Collect results
    char** result = (char**)malloc(10000 * sizeof(char*)); // Arbitrary large size
    int resultCount = 0;

    int len = strlen(s);
    for (int i = 0; i <= len - 10; i++) {
        insert(s + i);
    }

    // Gather substrings that appear more than once
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        Node* node = hashMap[i];
        while (node) {
            if (node->count > 1) {
                result[resultCount++] = node->substring;
            } else {
                free(node->substring);
            }
            Node* temp = node;
            node = node->next;
            free(temp);
        }
    }

    *returnSize = resultCount;
    return result;
}
