// Source: https://leetcode.com/problems/delete-columns-to-make-sorted-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of n strings strs, all of the same length.
//
// We may choose any deletion indices, and we delete all the characters in those indices for each string.
//
// For example, if we have strs = ["abcdef","uvwxyz"] and deletion indices {0, 2, 3}, then the final array after deletions is ["bef", "vyz"].
//
// Suppose we chose a set of deletion indices answer such that after deletions, the final array has every string (row) in lexicographic order. (i.e., (strs[0][0] <= strs[0][1] <= ... <= strs[0][strs[0].length - 1]), and (strs[1][0] <= strs[1][1] <= ... <= strs[1][strs[1].length - 1]), and so on). Return the minimum possible value of answer.length.
//
// Example:
// Input: strs = ["babca","bbazb"]
// Output: 3
// Explanation: After deleting columns 0, 1, and 4, the final array is strs = ["bc", "az"].
// Both these rows are individually in lexicographic order (ie. strs[0][0] <= strs[0][1] and strs[1][0] <= strs[1][1]).
// Note that strs[0] > strs[1] - the array strs is not necessarily in lexicographic order.
//
// Constraints:
// n == strs.length
// 	1 <= n <= 100
// 	1 <= strs[i].length <= 100
// 	strs[i] consists of lowercase English letters.
//
// Helpful references (internal KB):
// - Longest Increasing Subsequence (array, dp-1d)
//   • When to use: When you need to find the maximum length of a subsequence where elements are strictly increasing. It is applicable for problems requiring optimal ordering of non-contiguous elements.
//   • Idea: This DP approach calculates the length of the longest increasing subsequence ending at each position in an array. It builds upon previously computed subsequence lengths, resulting in an O(N^2) time complexity.
//   • Invariants: dp[i] stores the length of the LIS ending at index i.; For any j < i, if A[j] < A[i], then dp[j] + 1 is a candidate length for dp[i].
//   • Tips: Initialize DP array with 1s, as each element itself forms an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling the strict increasing condition (e.g., allowing equality).
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Longest Increasing Subsequence (array, coordinate-compress, segment-tree, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements must be strictly increasing. It is applicable for problems requiring optimal substructure on sequences with an increasing property.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements of the subsequence are in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search or a segment tree with coordinate compression.
//   • Invariants: The `dp` array (or segment tree) stores information about the smallest ending element for increasing subsequences of various lengths.; The `dp` array, if used, remains sorted in strictly increasing order.
//   • Tips: The O(N log N) solution uses a `dp` array storing the smallest ending element for all increasing subsequences of a given length.; Binary search (`lower_bound`) efficiently finds the correct position to update in the `dp` array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates; LIS typically requires strictly increasing elements.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minDeletionSize(char** strs, int strsSize) {
    int m = strlen(strs[0]);
    int dp[m];
    for (int i = 0; i < m; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            bool increasing = true;
            for (int k = 0; k < strsSize; k++) {
                if (strs[k][j] > strs[k][i]) {
                    increasing = false;
                    break;
                }
            }
            if (increasing) {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
    }
    int maxLen = 0;
    for (int i = 0; i < m; i++) {
        maxLen = fmax(maxLen, dp[i]);
    }
    return m - maxLen;      
}
