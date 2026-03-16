// Source: https://leetcode.com/problems/minimum-changes-to-make-k-semi-palindromes/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s and an integer k, partition s into k substrings such that the letter changes needed to make each substring a semi-palindrome are minimized.
//
// Return the minimum number of letter changes required.
//
// A semi-palindrome is a special type of string that can be divided into palindromes based on a repeating pattern. To check if a string is a semi-palindrome:​
//
//
// 	Choose a positive divisor d of the string's length. d can range from 1 up to, but not including, the string's length. For a string of length 1, it does not have a valid divisor as per this definition, since the only divisor is its length, which is not allowed.
// 	For a given divisor d, divide the string into groups where each group contains characters from the string that follow a repeating pattern of length d. Specifically, the first group consists of characters at positions 1, 1 + d, 1 + 2d, and so on; the second group includes characters at positions 2, 2 + d, 2 + 2d, etc.
// 	The string is considered a semi-palindrome if each of these groups forms a palindrome.
//
//
// Consider the string "abcabc":
//
//
// 	The length of "abcabc" is 6. Valid divisors are 1, 2, and 3.
// 	For d = 1: The entire string "abcabc" forms one group. Not a palindrome.
// 	For d = 2:
// 	
// 		Group 1 (positions 1, 3, 5): "acb"
// 		Group 2 (positions 2, 4, 6): "bac"
// 		Neither group forms a palindrome.
// 	
// 	
// 	For d = 3:
// 	
// 		Group 1 (positions 1, 4): "aa"
// 		Group 2 (positions 2, 5): "bb"
// 		Group 3 (positions 3, 6): "cc"
// 		All groups form palindromes. Therefore, "abcabc" is a semi-palindrome.
//
// Example:
// Input:   s = "abcac", k = 2 
//
// Output:   1 
//
// Explanation:  Divide s into "ab" and "cac". "cac" is already semi-palindrome. Change "ab" to "aa", it becomes semi-palindrome with d = 1.
//
// Constraints:
// 2 <= s.length <= 200
// 	1 <= k <= s.length / 2
// 	s contains only lowercase English letters.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
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

int minimumChanges(char* s, int k) {
    int n = strlen(s);
    int dp[201][201]; // dp[i][j]: min changes to partition first i chars into j semi-palindromes
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= k; ++j)
            dp[i][j] = 1e9;
    dp[0][0] = 0;

    // Precompute cost to make s[l..r-1] a semi-palindrome
    int cost[201][201];
    for (int l = 0; l < n; ++l) {
        for (int r = l + 1; r <= n; ++r) {
            int len = r - l;
            cost[l][r] = 1e9;
            for (int d = 1; d < len; ++d) {
                if (len % d != 0) continue;
                int changes = 0;
                for (int start = 0; start < d; ++start) {
                    int count[26] = {0};
                    int total = 0;
                    for (int pos = start; pos < len; pos += d) {
                        count[s[l + pos] - 'a']++;
                        total++;
                    }
                    int maxCount = 0;
                    for (int c = 0; c < 26; ++c)
                        if (count[c] > maxCount)
                            maxCount = count[c];
                    changes += total - maxCount;
                }
                if (changes < cost[l][r])
                    cost[l][r] = changes;
            }
        }
    }

    // DP to find minimum changes
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            for (int p = 0; p < i; ++p) {
                if (dp[p][j - 1] + cost[p][i] < dp[i][j]) {
                    dp[i][j] = dp[p][j - 1] + cost[p][i];
                }
            }
        }
    }

    return dp[n][k];        
}
