// Source: https://leetcode.com/problems/shortest-uncommon-substring-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array arr of size n consisting of non-empty strings.
//
// Find a string array answer of size n such that:
//
//
// 	answer[i] is the shortest substring of arr[i] that does not occur as a substring in any other string in arr. If multiple such substrings exist, answer[i] should be the lexicographically smallest. And if no such substring exists, answer[i] should be an empty string.
//
//
// Return the array answer.
//
// Example:
// Input: arr = ["cab","ad","bad","c"]
// Output: ["ab","","ba",""]
// Explanation: We have the following:
// - For the string "cab", the shortest substring that does not occur in any other string is either "ca" or "ab", we choose the lexicographically smaller substring, which is "ab".
// - For the string "ad", there is no substring that does not occur in any other string.
// - For the string "bad", the shortest substring that does not occur in any other string is "ba".
// - For the string "c", there is no substring that does not occur in any other string.
//
// Constraints:
// n == arr.length
// 	2 <= n <= 100
// 	1 <= arr[i].length <= 20
// 	arr[i] consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

#include <stdlib.h>
#include <string.h>

/* Check if substring sub of length subLen exists in str */
static int substringExists(const char *str, int strLen, const char *sub, int subLen) {
    if (subLen > strLen) return 0;
    for (int i = 0; i <= strLen - subLen; ++i) {
        if (strncmp(str + i, sub, subLen) == 0) return 1;
    }
    return 0;
}

/* Check if sub exists in any string in arr except at index skipIdx */
static int substringExistsInOther(char **arr, int arrSize, int skipIdx, 
                                   const char *sub, int subLen) {
    for (int i = 0; i < arrSize; ++i) {
        if (i == skipIdx) continue;
        if (substringExists(arr[i], strlen(arr[i]), sub, subLen)) {
            return 1;
        }
    }
    return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** shortestSubstrings(char** arr, int arrSize, int* returnSize) {
    *returnSize = arrSize;
    char **result = (char**)malloc(arrSize * sizeof(char*));
    if (!result) return NULL;
    
    for (int i = 0; i < arrSize; ++i) {
        char *str = arr[i];
        int strLen = strlen(str);
        char *answer = NULL;
        int answerLen = INT_MAX;
        
        /* Try all substrings by length, then lexicographical order */
        for (int len = 1; len <= strLen; ++len) {
            for (int start = 0; start <= strLen - len; ++start) {
                char sub[21]; /* max substring length is 20 */
                strncpy(sub, str + start, len);
                sub[len] = '\0';
                
                /* Check if this substring does not exist in other strings */
                if (!substringExistsInOther(arr, arrSize, i, sub, len)) {
                    /* Found a valid substring; since we iterate by increasing length,
                       and by lexicographical order within same length, take the first one */
                    if (!answer || len < answerLen || 
                        (len == answerLen && strcmp(sub, answer) < 0)) {
                        free(answer);
                        answer = (char*)malloc((len + 1) * sizeof(char));
                        if (!answer) {
                            free(result);
                            return NULL;
                        }
                        strcpy(answer, sub);
                        answerLen = len;
                    }
                }
            }
            if (answer && answerLen == len) break; /* Found shortest, no need to continue */
        }
        
        if (!answer) {
            /* No substring found; set to empty string */
            answer = (char*)malloc(1);
            if (!answer) {
                free(result);
                return NULL;
            }
            answer[0] = '\0';
        }
        
        result[i] = answer;
    }
    
    return result;
}
