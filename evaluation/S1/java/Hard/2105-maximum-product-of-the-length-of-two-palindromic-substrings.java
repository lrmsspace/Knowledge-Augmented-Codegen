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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long maxProduct(String s) {
        int n = s.length();
        int[] dOdd = new int[n];
        // Manacher's Algorithm to find all odd-length palindromic substrings
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 1 : Math.min(dOdd[l + r - i], r - i + 1);
            while (0 <= i - k && i + k < n && s.charAt(i - k) == s.charAt(i + k)) {
                k++;
            }
            dOdd[i] = k--;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
        }

        // Precompute max palindrome lengths from the left
        int[] maxLenLeft = new int[n];
        int maxLen = 0;
        for (int i = 0; i < n; i++) {
            int len = 2 * dOdd[i] - 1;
            int start = i - dOdd[i] + 1;
            maxLen = Math.max(maxLen, len);
            maxLenLeft[i] = Math.max(i > 0 ? maxLenLeft[i - 1] : 0, maxLen);
        }

        // Precompute max palindrome lengths from the right
        int[] maxLenRight = new int[n];
        maxLen = 0;
        for (int i = n - 1; i >= 0; i--) {
            int len = 2 * dOdd[i] - 1;
            int end = i + dOdd[i] - 1;
            maxLen = Math.max(maxLen, len);
            maxLenRight[i] = Math.max(i < n - 1 ? maxLenRight[i + 1] : 0, maxLen);
        }

        // Calculate the maximum product of lengths of two non-intersecting palindromic substrings
        long result = 0;
        for (int i = 0; i < n - 1; i++) {
            result = Math.max(result, (long) maxLenLeft[i] * maxLenRight[i + 1]);
        }

        return result;          
    }
}
