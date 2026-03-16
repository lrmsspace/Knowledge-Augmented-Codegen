// Source: https://leetcode.com/problems/number-of-lines-to-write-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s of lowercase English letters and an array widths denoting how many pixels wide each lowercase English letter is. Specifically, widths[0] is the width of 'a', widths[1] is the width of 'b', and so on.
//
// You are trying to write s across several lines, where each line is no longer than 100 pixels. Starting at the beginning of s, write as many letters on the first line such that the total width does not exceed 100 pixels. Then, from where you stopped in s, continue writing as many letters as you can on the second line. Continue this process until you have written all of s.
//
// Return an array result of length 2 where:
//
//
// 	result[0] is the total number of lines.
// 	result[1] is the width of the last line in pixels.
//
// Example:
// Input: widths = [10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10], s = "abcdefghijklmnopqrstuvwxyz"
// Output: [3,60]
// Explanation: You can write s as follows:
// abcdefghij  // 100 pixels wide
// klmnopqrst  // 100 pixels wide
// uvwxyz      // 60 pixels wide
// There are a total of 3 lines, and the last line is 60 pixels wide.
//
// Constraints:
// widths.length == 26
// 	2 <= widths[i] <= 10
// 	1 <= s.length <= 1000
// 	s contains only lowercase English letters.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, two-pointers)
//   • When to use: When efficiently searching for all occurrences of a pattern string within a larger text string, or when computing the longest proper prefix of a string that is also a suffix for all its prefixes.
//   • Idea: The KMP algorithm efficiently finds all occurrences of a pattern within a text by pre-processing the pattern to build a prefix function (LPS array), which avoids redundant character comparisons. It achieves a time complexity of O(N + M) for text length N and pattern length M.
//   • Invariants: The prefix function array `pi` stores for each `i` the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation for `pi[i]`, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix of `s[0...i-1]`.
//   • Tips: Precompute the prefix function (LPS array) for the pattern to guide shifts.; Use two pointers: one for the text (or current character in pattern for prefix function), one for the pattern (or length of matched prefix).
//   • Pitfalls: Incorrectly calculating or using the prefix function values, leading to wrong shifts.; Off-by-one errors when indexing or shifting pointers, especially at boundaries.
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
int* numberOfLines(int* widths, int widthsSize, char * s, int* returnSize){
    int lines = 1, width = 0;
    for (int i = 0; s[i]; ++i) {
        int w = widths[s[i] - 'a'];
        if (width + w > 100) {
            ++lines;
            width = w;
        } else {
            width += w;
        }
    }
    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = lines;
    result[1] = width;
    *returnSize = 2;
    return result;
}
