// Source: https://leetcode.com/problems/longest-string-chain/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of words where each word consists of lowercase English letters.
//
// wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB.
//
//
// 	For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
//
//
// A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain with k == 1.
//
// Return the length of the longest possible word chain with words chosen from the given list of words.
//
// Example:
// Input: words = ["a","b","ba","bca","bda","bdca"]
// Output: 4
// Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 16
// 	words[i] only consists of lowercase English letters.
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Longest Increasing Subsequence (array, dp-1d)
//   • When to use: When you need to find the maximum length of a subsequence where elements are strictly increasing. It is applicable for problems requiring optimal ordering of non-contiguous elements.
//   • Idea: This DP approach calculates the length of the longest increasing subsequence ending at each position in an array. It builds upon previously computed subsequence lengths, resulting in an O(N^2) time complexity.
//   • Invariants: dp[i] stores the length of the LIS ending at index i.; For any j < i, if A[j] < A[i], then dp[j] + 1 is a candidate length for dp[i].
//   • Tips: Initialize DP array with 1s, as each element itself forms an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling the strict increasing condition (e.g., allowing equality).
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int longestStrChain(char** words, int wordsSize) {
    // Sort the words by length
    qsort(words, wordsSize, sizeof(char*), [](const void* a, const void* b) {
        return strlen(*(const char**)a) - strlen(*(const char**)b);
    });

    int dp[wordsSize];
    for (int i = 0; i < wordsSize; i++) {
        dp[i] = 1; // Each word is a chain of length 1
    }

    int maxChainLength = 1;

    for (int i = 0; i < wordsSize; i++) {
        for (int j = 0; j < i; j++) {
            if (strlen(words[i]) == strlen(words[j]) + 1 && isPredecessor(words[j], words[i])) {
                dp[i] = dp[j] + 1;
                if (dp[i] > maxChainLength) {
                    maxChainLength = dp[i];
                }
            }
        }
    }

    return maxChainLength;      
}
