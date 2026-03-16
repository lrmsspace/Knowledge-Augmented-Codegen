// Source: https://leetcode.com/problems/decremental-string-concatenation/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array words containing n strings.
//
// Let's define a join operation join(x, y) between two strings x and y as concatenating them into xy. However, if the last character of x is equal to the first character of y, one of them is deleted.
//
// For example join("ab", "ba") = "aba" and join("ab", "cde") = "abcde".
//
// You are to perform n - 1 join operations. Let str0 = words[0]. Starting from i = 1 up to i = n - 1, for the ith operation, you can do one of the following:
//
//
// 	Make stri = join(stri - 1, words[i])
// 	Make stri = join(words[i], stri - 1)
//
//
// Your task is to minimize the length of strn - 1.
//
// Return an integer denoting the minimum possible length of strn - 1.
//
// Example:
// Input: words = ["aa","ab","bc"]
// Output: 4
// Explanation: In this example, we can perform join operations in the following order to minimize the length of str2: 
// str0 = "aa"
// str1 = join(str0, "ab") = "aab"
// str2 = join(str1, "bc") = "aabc" 
// It can be shown that the minimum possible length of str2 is 4.
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 50
// 	Each character in words[i] is an English lowercase letter
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
//   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
//   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
//   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
//   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimizeConcatenatedLength(String[] words) {
        int n = words.length;
        int[][] dp = new int[n][n];
        for (int i = 0; i < n; i++) {
            dp[i][i] = words[i].length();
        }
        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                dp[l][r] = Math.min(dp[l][r - 1] + words[r].length() - (words[r].charAt(0) == words[r - 1].charAt(dp[l][r - 1] - 1) ? 1 : 0),
                                    dp[l + 1][r] + words[l].length() - (words[l].charAt(words[l].length() - 1) == words[l + 1].charAt(0) ? 1 : 0));
            }
        }
        return dp[0][n - 1];            
    }
}
