// Source: https://leetcode.com/problems/minimum-window-substring/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".
//
// The testcases will be generated such that the answer is unique.
//
// Example:
// Input: s = "ADOBECODEBANC", t = "ABC"
// Output: "BANC"
// Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
//
// Constraints:
// m == s.length
// 	n == t.length
// 	1 <= m, n <= 105
// 	s and t consist of uppercase and lowercase English letters.
//
//
//  
// Follow up: Could you find an algorithm that runs in O(m + n) time?
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* minWindow(char* s, char* t) {
    int need[128] = {0}, window[128] = {0};
    int required = 0, formed = 0;
    int left = 0, right = 0;
    int minLen = __INT_MAX__, minLeft = 0;

    for (int i = 0; t[i]; ++i) {
        if (need[(unsigned char)t[i]] == 0) required++;
        need[(unsigned char)t[i]]++;
    }

    while (s[right]) {
        char c = s[right];
        window[(unsigned char)c]++;
        if (need[(unsigned char)c] > 0 && window[(unsigned char)c] == need[(unsigned char)c]) {
            formed++;
        }

        while (left <= right && formed == required) {
            c = s[left];
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minLeft = left;
            }
            window[(unsigned char)c]--;
            if (need[(unsigned char)c] > 0 && window[(unsigned char)c] < need[(unsigned char)c]) {
                formed--;
            }
            left++;
        }
        right++;
    }

    if (minLen == __INT_MAX__) return "";
    char* result = (char*)malloc((minLen + 1) * sizeof(char));
    if (!result) return "";
    strncpy(result, s + minLeft, minLen);
    result[minLen] = '\0';
    return result;      
}
