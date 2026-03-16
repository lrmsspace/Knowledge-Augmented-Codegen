// Source: https://leetcode.com/problems/check-if-string-is-transformable-with-substring-sort-operations/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t, transform string s into string t using the following operation any number of times:
//
//
// 	Choose a non-empty substring in s and sort it in place so the characters are in ascending order.
//
// 	
// 		For example, applying the operation on the underlined substring in "14234" results in "12344".
// 	
// 	
//
//
// Return true if it is possible to transform s into t. Otherwise, return false.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "84532", t = "34852"
// Output: true
// Explanation: You can transform s into t using the following sort operations:
// "84532" (from index 2 to 3) -> "84352"
// "84352" (from index 0 to 2) -> "34852"
//
// Constraints:
// s.length == t.length
// 	1 <= s.length <= 105
// 	s and t consist of only digits.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
//   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
//   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
//   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isTransformable(char* s, char* t) {
    int n = strlen(s);
    int count[10][n];
    memset(count, 0, sizeof(count));
    
    for (int i = 0; i < n; i++) {
        int digit = s[i] - '0';
        for (int d = 0; d < 10; d++) {
            count[d][i] = (i > 0 ? count[d][i - 1] : 0) + (d == digit ? 1 : 0);
        }
    }
    
    for (int i = n - 1; i >= 0; i--) {
        int digit = t[i] - '0';
        if (count[digit][i] == 0) {
            return false;
        }
        for (int d = 0; d < digit; d++) {
            if (count[d][i] > 0) {
                return false;
            }
        }
    }
    
    return true;        
}
