// Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a palindromic string s and an integer k.
//
// Return the k-th lexicographically smallest palindromic permutation of s. If there are fewer than k distinct palindromic permutations, return an empty string.
//
// Note: Different rearrangements that yield the same palindromic string are considered identical and are counted once.
//
// Example:
// Input: s = "abba", k = 2
//
// Output: "baab"
//
// Explanation:
//
//
// 	The two distinct palindromic rearrangements of "abba" are "abba" and "baab".
// 	Lexicographically, "abba" comes before "baab". Since k = 2, the output is "baab".
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of lowercase English letters.
// 	s is guaranteed to be palindromic.
// 	1 <= k <= 106
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
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
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* smallestPalindrome(char* s, int k) {
    int count[26] = {0};
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        count[s[i] - 'a']++;
    }

    char half[5000 + 1]; /* half length max 5000 for s length max 10000 */
    int halfLen = 0;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < count[i] / 2; ++j) {
            half[halfLen++] = 'a' + i;
        }
    }
    half[halfLen] = '\0';

    /* Generate k-th lexicographical permutation of half */
    char *resultHalf = (char*)malloc((halfLen + 1) * sizeof(char));
    if (!resultHalf) return NULL;
    strcpy(resultHalf, half);

    int *used = (int*)calloc(halfLen, sizeof(int));
    if (!used) {
        free(resultHalf);
        return NULL;
    }

    char *perm = (char*)malloc((halfLen + 1) * sizeof(char));
    if (!perm) {
        free(resultHalf);
        free(used);
        return NULL;
    }
    perm[halfLen] = '\0';

    int fact[halfLen + 1];
    fact[0] = 1;
    for (int i = 1; i <= halfLen; ++i) {
        fact[i] = fact[i - 1] * i;
    }

    int totalPerms = fact[halfLen];
    for (int i = 0; i < 26; ++i) {
        if (count[i] / 2 > 1) {
            totalPerms /= fact[count[i] / 2];
        }
    }

    if (k > totalPerms) {
        free(resultHalf);
        free(used);
        free(perm);
        return "";
    }

    k--; /* convert to zero-based index */
    for (int i = 0; i < halfLen; ++i) {
        for (int j = 0; j < halfLen; ++j) {
            if (used[j]) continue;
            /* Count permutations with half[j] at position i */
            used[j] = 1;

            int perms = fact[halfLen - i - 1];
            int freq[26] = {0};
            for (int m = 0; m < halfLen; ++m) {
                if (!used[m]) {
                    freq[half[m] - 'a']++;
                }
            }
            for (int m = 0; m < 26; ++m) {
                if (freq[m] > 1) {
                    perms /= fact[freq[m]];
                }
            }

            if (k < perms) {
                perm[i] = half[j];
                break;
            } else {
                k -= perms;
                used[j] = 0;
            }
        }
    }
    free(used);
    free(resultHalf);
    /* Construct full palindrome */
    char *palindrome = (char*)malloc((len + 1) * sizeof(char));
    if (!palindrome) {
        free(perm);
        return NULL;
    }
    for (int i = 0; i < halfLen; ++i) {
        palindrome[i] = perm[i];
    }
    if (len % 2 == 1) {
        for (int i = 0; i < 26; ++i) {
            if (count[i] % 2 == 1) {
                palindrome[halfLen] = 'a' + i;
                break;
            }
        }
        for (int i = halfLen - 1; i >= 0; --i) {
            palindrome[len - 1 - i] = perm[i];
        }
    } else {
        for (int i = halfLen - 1; i >= 0; --i) {
            palindrome[len - 1 - i] = perm[i];
        }
    }
    palindrome[len] = '\0';
    free(perm); 
    return palindrome;
}
