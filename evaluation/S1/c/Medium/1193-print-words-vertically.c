// Source: https://leetcode.com/problems/print-words-vertically/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s. Return all the words vertically in the same order in which they appear in s.
// Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
// Each word would be put on only one column and that in one column there will be only one word.
//
// Example:
// Input: s = "HOW ARE YOU"
// Output: ["HAY","ORO","WEU"]
// Explanation: Each word is printed vertically. 
//  "HAY"
//  "ORO"
//  "WEU"
//
// Constraints:
// 1 <= s.length <= 200
// 	s contains only upper case English letters.
// 	It's guaranteed that there is only one space between 2 words.
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, greedy, dp-1d)
//   • When to use: Use when finding the longest sequence of elements in a given array such that each element is greater than the preceding one, without changing their relative order. It's applicable for optimizing problems involving ordered subsets.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of an array where elements are in strictly increasing order. It can be solved in O(N log N) time using a greedy approach with binary search, or O(N^2) using dynamic programming.
//   • Invariants: The 'tails' array elements are always in strictly increasing order.; tails[i] stores the smallest possible ending element of an increasing subsequence of length i+1.
//   • Tips: Prefer the O(N log N) greedy approach with binary search for better performance.; The 'tails' array in the greedy approach stores the smallest tail of all increasing subsequences of a certain length.
//   • Pitfalls: Confusing LIS with Longest Common Subsequence (LCS) or contiguous subarrays.; Incorrectly handling duplicate elements when 'strictly increasing' is required.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
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
char ** printVertically(char * s, int* returnSize){
    // Split the input string into words
    char *words[100];
    int wordCount = 0;
    char *token = strtok(s, " ");
    while (token != NULL) {
        words[wordCount++] = token;
        token = strtok(NULL, " ");
    }

    // Find the maximum length of the words
    int maxLength = 0;
    for (int i = 0; i < wordCount; i++) {
        int len = strlen(words[i]);
        if (len > maxLength) {
            maxLength = len;
        }
    }

    // Prepare the result array
    char **result = (char **)malloc(maxLength * sizeof(char *));
    for (int i = 0; i < maxLength; i++) {
        result[i] = (char *)malloc((wordCount + 1) * sizeof(char));
        memset(result[i], ' ', wordCount);
        result[i][wordCount] = '\0';
    }

    // Fill the result array with vertical words
    for (int i = 0; i < wordCount; i++) {
        for (int j = 0; j < strlen(words[i]); j++) {
            result[j][i] = words[i][j];
        }
    }

    // Trim trailing spaces from each string in the result
    for (int i = 0; i < maxLength; i++) {
        int end = wordCount - 1;
        while (end >= 0 && result[i][end] == ' ') {
            end--;
        }
        result[i][end + 1] = '\0';
    }

    *returnSize = maxLength;
    return result;
}
