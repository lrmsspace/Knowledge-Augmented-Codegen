// Source: https://leetcode.com/problems/palindrome-rearrangement-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string s having an even length n.
//
// You are also given a 0-indexed 2D integer array, queries, where queries[i] = [ai, bi, ci, di].
//
// For each query i, you are allowed to perform the following operations:
//
//
// 	Rearrange the characters within the substring s[ai:bi], where 0 <= ai <= bi < n / 2.
// 	Rearrange the characters within the substring s[ci:di], where n / 2 <= ci <= di < n.
//
//
// For each query, your task is to determine whether it is possible to make s a palindrome by performing the operations.
//
// Each query is answered independently of the others.
//
// Return a 0-indexed array answer, where answer[i] == true if it is possible to make s a palindrome by performing operations specified by the ith query, and false otherwise.
//
//
// 	A substring is a contiguous sequence of characters within a string.
// 	s[x:y] represents the substring consisting of characters from the index x to index y in s, both inclusive.
//
// Example:
// Input: s = "abcabc", queries = [[1,1,3,5],[0,2,5,5]]
// Output: [true,true]
// Explanation: In this example, there are two queries:
// In the first query:
// - a0 = 1, b0 = 1, c0 = 3, d0 = 5.
// - So, you are allowed to rearrange s[1:1] => abcabc and s[3:5] => abcabc.
// - To make s a palindrome, s[3:5] can be rearranged to become => abccba.
// - Now, s is a palindrome. So, answer[0] = true.
// In the second query:
// - a1 = 0, b1 = 2, c1 = 5, d1 = 5.
// - So, you are allowed to rearrange s[0:2] => abcabc and s[5:5] => abcabc.
// - To make s a palindrome, s[0:2] can be rearranged to become => cbaabc.
// - Now, s is a palindrome. So, answer[1] = true.
//
// Constraints:
// 2 <= n == s.length <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 4
// 	ai == queries[i][0], bi == queries[i][1]
// 	ci == queries[i][2], di == queries[i][3]
// 	0 <= ai <= bi < n / 2
// 	n / 2 <= ci <= di < n 
// 	n is even.
// 	s consists of only lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Fenwick Tree (array, bit-fenwick, prefix-sum)
//   • When to use: When you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It is ideal for scenarios requiring both fast query and update operations on an array.
//   • Idea: A Fenwick tree, or Binary Indexed Tree (BIT), is an array-based data structure that efficiently calculates prefix sums and updates individual elements in an array. It supports both point updates and prefix sum queries in O(log N) time complexity.
//   • Invariants: Each `T[i]` stores the sum of a specific range `[g(i), i]` from the original array.; The `sum(idx)` function correctly aggregates values from `A[0]` to `A[idx]`.
//   • Tips: Understand the bit manipulation (`i & -i`) for navigating parent/child relationships.; Consistently choose and apply either 0-based or 1-based indexing throughout the implementation.
//   • Pitfalls: Incorrectly handling 0-based versus 1-based indexing can lead to off-by-one errors.; Forgetting to initialize the tree or performing updates incorrectly will yield wrong results.
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
bool* canMakePalindromeQueries(char* s, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!s || !queries || queriesSize <= 0 || !queriesColSize || !returnSize) {
        return NULL;
    }

    int n = strlen(s);
    int half = n / 2;

    // Precompute prefix parity bitmasks for both halves
    int *prefixLeft = (int*)malloc((half + 1) * sizeof(int));
    int *prefixRight = (int*)malloc((half + 1) * sizeof(int));
    if (!prefixLeft || !prefixRight) {
        free(prefixLeft);
        free(prefixRight);
        return NULL;
    }
    prefixLeft[0] = 0;
    prefixRight[0] = 0;

    for (int i = 0; i < half; ++i) {
        prefixLeft[i + 1] = prefixLeft[i] ^ (1 << (s[i] - 'a'));
        prefixRight[i + 1] = prefixRight[i] ^ (1 << (s[n - 1 - i] - 'a'));
    }

    // Process each query
    bool *results = (bool*)malloc(queriesSize * sizeof(bool));
    if (!results) {
        free(prefixLeft);
        free(prefixRight);
        return NULL;
    }

    for (int i = 0; i < queriesSize; ++i) {
        int a = queries[i][0];
        int b = queries[i][1];
        int c = queries[i][2];
        int d = queries[i][3];

        int leftMask = prefixLeft[b + 1] ^ prefixLeft[a];
        int rightMask = prefixRight[d - half + 1] ^ prefixRight[c - half];

        int combinedMask = leftMask ^ rightMask;

        // Check if at most one bit is set in combinedMask
        results[i] = (combinedMask & (combinedMask - 1)) == 0;
    }

    free(prefixLeft);
    free(prefixRight);

    *returnSize = queriesSize;
    return results;     
}
