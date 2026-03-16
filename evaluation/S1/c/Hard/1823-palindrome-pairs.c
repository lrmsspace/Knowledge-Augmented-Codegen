// Source: https://leetcode.com/problems/palindrome-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of unique strings words.
//
// A palindrome pair is a pair of integers (i, j) such that:
//
//
//  0 <= i, j < words.length,
//  i != j, and
//  words[i] + words[j] (the concatenation of the two strings) is a palindrome.
//
//
// Return an array of all the palindrome pairs of words.
//
// You must write an algorithm with O(sum of words[i].length) runtime complexity.
//
// Example:
// Input: words = ["abcd","dcba","lls","s","sssll"]
// Output: [[0,1],[1,0],[3,2],[2,4]]
// Explanation: The palindromes are ["abcddcba","dcbaabcd","slls","llssssll"]
//
// Constraints:
// 1 <= words.length <= 5000
//  0 <= words[i].length <= 300
//  words[i] consists of lowercase English letters.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** palindromePairs(char** words, int wordsSize, int* returnSize, int** returnColumnSizes) {
    #define MAX_PAIRS 10000
    #define MAX_WORD_LENGTH 300
    #define BASE 131
    #define MOD 1000000007

    typedef struct TrieNode {
        int index;
        struct TrieNode* children[26];
    } TrieNode;

    TrieNode* createNode() {
        TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
        node->index = -1;
        for (int i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
        return node;
    }

    void insert(TrieNode* root, const char* word, int index) {
        TrieNode* curr = root;
        for (int i = strlen(word) - 1; i >= 0; i--) {
            int c = word[i] - 'a';
            if (!curr->children[c]) {
                curr->children[c] = createNode();
            }
            curr = curr->children[c];
        }
        curr->index = index;
    }

    int isPalindrome(const char* word, int left, int right) {
        while (left < right) {
            if (word[left++] != word[right--]) return 0;
        }
        return 1;
    }

    TrieNode* root = createNode();
    for (int i = 0; i < wordsSize; i++) {
        insert(root, words[i], i);
    }

    int** result = (int**)malloc(MAX_PAIRS * sizeof(int*));
    *returnColumnSizes = (int*)malloc(MAX_PAIRS * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < wordsSize; i++) {
        const char* word = words[i];
        int len = strlen(word);
        for (int j = 0; j <= len; j++) {
            // Check prefix
            if (isPalindrome(word, j, len - 1)) {
                TrieNode* curr = root;
                for (int k = 0; k < j; k++) {
                    int c = word[k] - 'a';
                    if (!curr->children[c]) break;
                    curr = curr->children[c];
                }
                if (curr && curr->index != -1 && curr->index != i) {
                    result[*returnSize] = (int*)malloc(2 * sizeof(int));
                    result[*returnSize][0] = i;
                    result[*returnSize][1] = curr->index;
                    (*returnColumnSizes)[*returnSize] = 2;
                    (*returnSize)++;
                }
            }
            // Check suffix
            if (j > 0 && isPalindrome(word, 0, j - 1)) {
                TrieNode* curr = root;
                for (int k = len - 1; k >= j; k--) {
                    int c = word[k] - 'a';
                    if (!curr->children[c]) break;
                    curr = curr->children[c];
                }
                if (curr && curr->index != -1 && curr->index != i) {
                    result[*returnSize] = (int*)malloc(2 * sizeof(int));
                    result[*returnSize][0] = curr->index;
                    result[*returnSize][1] = i;
                    (*returnColumnSizes)[*returnSize] = 2;
                    (*returnSize)++;
                }
            }
        }
    }
    return result;
}
