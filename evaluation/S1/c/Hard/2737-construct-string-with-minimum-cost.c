// Source: https://leetcode.com/problems/construct-string-with-minimum-cost/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string target, an array of strings words, and an integer array costs, both arrays of the same length.
//
// Imagine an empty string s.
//
// You can perform the following operation any number of times (including zero):
//
//
// 	Choose an index i in the range [0, words.length - 1].
// 	Append words[i] to s.
// 	The cost of operation is costs[i].
//
//
// Return the minimum cost to make s equal to target. If it's not possible, return -1.
//
// Example:
// Input: target = "abcdef", words = ["abdef","abc","d","def","ef"], costs = [100,1,1,10,5]
//
// Output: 7
//
// Explanation:
//
// The minimum cost can be achieved by performing the following operations:
//
//
// 	Select index 1 and append "abc" to s at a cost of 1, resulting in s = "abc".
// 	Select index 2 and append "d" to s at a cost of 1, resulting in s = "abcd".
// 	Select index 4 and append "ef" to s at a cost of 5, resulting in s = "abcdef".
//
// Constraints:
// 1 <= target.length <= 5 * 104
// 	1 <= words.length == costs.length <= 5 * 104
// 	1 <= words[i].length <= target.length
// 	The total sum of words[i].length is less than or equal to 5 * 104.
// 	target and words[i] consist only of lowercase English letters.
// 	1 <= costs[i] <= 104
//
// Helpful references (internal KB):
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
//   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
//   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
//   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
//   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
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

int minimumCost(char* target, char** words, int wordsSize, int* costs, int costsSize) {
    int n = strlen(target);
    int *dp = (int*)malloc((n + 1) * sizeof(int));
    if (!dp) return -1;
    for (int i = 0; i <= n; ++i) dp[i] = 1000000000; /* large number */
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w < wordsSize; ++w) {
            int len = strlen(words[w]);
            if (len <= i && strncmp(&target[i - len], words[w], len) == 0) {
                if (dp[i - len] != 1000000000) {
                    if (dp[i] > dp[i - len] + costs[w]) {
                        dp[i] = dp[i - len] + costs[w];
                    }
                }
            }
        }
    }

    int result = (dp[n] == 1000000000) ? -1 : dp[n];
    free(dp);
    return result;      
}
