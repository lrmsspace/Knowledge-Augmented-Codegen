// Source: https://leetcode.com/problems/maximize-palindrome-length-from-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings, word1 and word2. You want to construct a string in the following manner:
//
//
// 	Choose some non-empty subsequence subsequence1 from word1.
// 	Choose some non-empty subsequence subsequence2 from word2.
// 	Concatenate the subsequences: subsequence1 + subsequence2, to make the string.
//
//
// Return the length of the longest palindrome that can be constructed in the described manner. If no palindromes can be constructed, return 0.
//
// A subsequence of a string s is a string that can be made by deleting some (possibly none) characters from s without changing the order of the remaining characters.
//
// A palindrome is a string that reads the same forward as well as backward.
//
// Example:
// Input: word1 = "cacb", word2 = "cbba"
// Output: 5
// Explanation: Choose "ab" from word1 and "cba" from word2 to make "abcba", which is a palindrome.
//
// Constraints:
// 1 <= word1.length, word2.length <= 1000
// 	word1 and word2 consist of lowercase English letters.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int longestPalindrome(char* word1, char* word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int totalLen = len1 + len2;
    char* combined = (char*)malloc(totalLen + 1);
    if (!combined) return 0;
    strcpy(combined, word1);
    strcpy(combined + len1, word2);

    // Manacher's algorithm to find all palindromic substrings
    int* d_odd = (int*)calloc(totalLen, sizeof(int));
    int* d_even = (int*)calloc(totalLen, sizeof(int));
    if (!d_odd || !d_even) {
        free(combined);
        free(d_odd);
        free(d_even);
        return 0;
    }

    // Odd-length palindromes
    for (int i = 0, l = 0, r = -1; i < totalLen; i++) {
        int k = (i > r) ? 1 : (d_odd[l + r - i] < r - i + 1 ? d_odd[l + r - i] : r - i + 1);
        while (0 <= i - k && i + k < totalLen && combined[i - k] == combined[i + k]) k++;
        d_odd[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    // Even-length palindromes
    for (int i = 0, l = 0, r = -1; i < totalLen; i++) {
        int k = (i > r) ? 0 : (d_even[l + r - i + 1] < r - i + 1 ? d_even[l + r - i + 1] : r - i + 1);
        while (0 <= i - k - 1 && i + k < totalLen && combined[i - k - 1] == combined[i + k]) k++;
        d_even[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }

    // Find the longest palindrome that crosses the boundary
    int maxLen = 0;
    for (int center = 0; center < totalLen; center++) {
        // Odd-length palindromes
        int radius = d_odd[center];
        int left = center - radius + 1;
        int right = center + radius - 1;
        if (left < len1 && right >= len1) {
            int palLen = 2 * (radius - 1) + 1;
            if (palLen > maxLen) {
                maxLen = palLen;
            }
        }

        // Even-length palindromes
        radius = d_even[center];
        left = center - radius;
        right = center + radius - 1;
        if (left < len1 && right >= len1) {
            int palLen = 2 * radius;
            if (palLen > maxLen) {
                maxLen = palLen;
            }
        }
    }
    free(combined);
    free(d_odd);
    free(d_even);
    return maxLen;
}
