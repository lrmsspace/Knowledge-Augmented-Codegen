// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and a positive integer k.
//
// Select a set of non-overlapping substrings from the string s that satisfy the following conditions:
//
//
// 	The length of each substring is at least k.
// 	Each substring is a palindrome.
//
//
// Return the maximum number of substrings in an optimal selection.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "abaccdbbd", k = 3
// Output: 2
// Explanation: We can select the substrings underlined in s = "abaccdbbd". Both "aba" and "dbbd" are palindromes and have a length of at least k = 3.
// It can be shown that we cannot find a selection with more than two valid substrings.
//
// Constraints:
// 1 <= k <= s.length <= 2000
// 	s consists of lowercase English letters.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxPalindromes(char* s, int k) {
    int n = strlen(s);
    /* Manacher's algorithm to find all palindromic substrings */
    int d_odd[2000];  /* d_odd[i]: radius of odd-length palindrome centered at i */
    int d_even[2000]; /* d_even[i]: radius of even-length palindrome centered at i */
    /* Odd-length palindromes */
    int l = 0, r = -1;
    for (int i = 0; i < n; ++i) {
        int k1 = (i > r) ? 1 : ((d_odd[l + r - i] < r - i + 1) ? d_odd[l + r - i] : r - i + 1);
        while (i - k1 >= 0 && i + k1 < n && s[i - k1] == s[i + k1]) ++k1;
        d_odd[i] = k1--;
        if (i + k1 > r) { l = i - k1; r = i + k1; }
    }
    /* Even-length palindromes */
    l = 0; r = -1;
    for (int i = 0; i < n; ++i) {
        int k1 = (i > r) ? 0 : ((d_even[l + r - i + 1] < r - i + 1) ? d_even[l + r - i + 1] : r - i + 1);
        while (i - k1 - 1 >= 0 && i + k1 < n && s[i - k1 - 1] == s[i + k1]) ++k1;
        d_even[i] = k1--;
        if (i + k1 > r) { l = i - k1 - 1; r = i + k1; }
    }
    /* Dynamic Programming to find maximum number of non-overlapping palindromic substrings */
    int dp[2001];
    for (int i = 0; i <= n; ++i) dp[i] = 0;
    for (int i = 0; i < n; ++i) {
        dp[i + 1] = (dp[i + 1] > dp[i]) ? dp[i + 1] : dp[i];
        /* Check odd-length palindromes */
        int radius = d_odd[i];
        for (int r1 = radius; r1 >= 1; --r1) {
            int start = i - r1 + 1;
            int end = i + r1 - 1;
            if (end - start + 1 >= k) {
                dp[end + 1] = (dp[end + 1] > dp[start] + 1) ? dp[end + 1] : dp[start] + 1;
                break; /* Only need the longest valid palindrome */
            }
        }
        /* Check even-length palindromes */
        radius = d_even[i];
        for (int r1 = radius; r1 >= 1; --r1) {
            int start = i - r1;
            int end = i + r1 - 1;
            if (end - start + 1 >= k) {
                dp[end + 1] = (dp[end + 1] > dp[start] + 1) ? dp[end + 1] : dp[start] + 1;
                break; /* Only need the longest valid palindrome */
            }
        }
    }
    return dp[n];
      
}
