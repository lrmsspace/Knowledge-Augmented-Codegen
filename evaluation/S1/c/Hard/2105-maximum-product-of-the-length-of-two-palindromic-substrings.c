// Source: https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-substrings/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string s and are tasked with finding two non-intersecting palindromic substrings of odd length such that the product of their lengths is maximized.
//
// More formally, you want to choose four integers i, j, k, l such that 0 <= i <= j < k <= l < s.length and both the substrings s[i...j] and s[k...l] are palindromes and have odd lengths. s[i...j] denotes a substring from index i to index j inclusive.
//
// Return the maximum possible product of the lengths of the two non-intersecting palindromic substrings.
//
// A palindrome is a string that is the same forward and backward. A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "ababbb"
// Output: 9
// Explanation: Substrings "aba" and "bbb" are palindromes with odd length. product = 3 * 3 = 9.
//
// Constraints:
// 2 <= s.length <= 105
// 	s consists of lowercase English letters.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
//   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
//   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
//   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
//   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long maxProduct(char* s) {
    int n = strlen(s);
    /* Manacher's Algorithm to find all odd-length palindromes */
    int *d_odd = (int*)malloc(n * sizeof(int));
    if (!d_odd) return 0;
    int l = 0, r = -1;
    for (int i = 0; i < n; ++i) {
        int k = (i > r) ? 1 : ((d_odd[l + r - i] < r - i + 1) ? d_odd[l + r - i] : r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) ++k;
        d_odd[i] = k--;
        if (i + k > r) { l = i - k; r = i + k; }
    }

    /* Precompute max palindrome lengths from left and right */
    int *max_left = (int*)malloc(n * sizeof(int));
    int *max_right = (int*)malloc(n * sizeof(int));
    if (!max_left || !max_right) {
        free(d_odd); free(max_left); free(max_right); return 0;
    }
    int max_len = 0;
    for (int i = 0; i < n; ++i) {
        int pal_len = 2 * d_odd[i] - 1;
        if (pal_len > max_len) max_len = pal_len;
        max_left[i] = max_len;
        if (i + 1 < n) {
            if (max_left[i + 1] < max_left[i]) max_left[i + 1] = max_left[i];
        }
    }
    max_len = 0;
    for (int i = n - 1; i >= 0; --i) {
        int pal_len = 2 * d_odd[i] - 1;
        if (pal_len > max_len) max_len = pal_len;
        max_right[i] = max_len;
        if (i - 1 >= 0) {
            if (max_right[i - 1] < max_right[i]) max_right[i - 1] = max_right[i];
        }
    }

    /* Compute maximum product of lengths */
    long long result = 0;
    for (int i = 0; i < n - 1; ++i) {
        long long product = (long long)max_left[i] * (long long)max_right[i + 1];
        if (product > result) result = product;
    }
    free(d_odd);
    free(max_left);
    free(max_right);
    return result;
}
