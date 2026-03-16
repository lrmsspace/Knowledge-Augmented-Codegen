// Source: https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s consisting of the characters 'a', 'b', and 'c' and a non-negative integer k. Each minute, you may take either the leftmost character of s, or the rightmost character of s.
//
// Return the minimum number of minutes needed for you to take at least k of each character, or return -1 if it is not possible to take k of each character.
//
// Example:
// Input: s = "aabaaaacaabc", k = 2
// Output: 8
// Explanation: 
// Take three characters from the left of s. You now have two 'a' characters, and one 'b' character.
// Take five characters from the right of s. You now have four 'a' characters, two 'b' characters, and two 'c' characters.
// A total of 3 + 5 = 8 minutes is needed.
// It can be proven that 8 is the minimum number of minutes needed.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only the letters 'a', 'b', and 'c'.
// 	0 <= k <= s.length
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Z-function and its calculation (string, array, two-pointers)
//   • When to use: Use when you need to find the length of the longest common prefix between a string and all its suffixes efficiently. It is fundamental for various string matching and pattern searching problems.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the original string and its suffix starting at index i. This algorithm calculates the entire Z-array in O(N) time complexity.
//   • Invariants: For all k < i, z[k] has been correctly computed.; The interval [l, r) always represents the rightmost segment match found so far.
//   • Tips: Leverage previously computed Z-values to avoid redundant comparisons.; Maintain a [l, r) window representing the rightmost segment match found so far.
//   • Pitfalls: Incorrectly handling the base case z[0] (usually set to 0).; Off-by-one errors when calculating the length of the prefix or updating the window.
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

int takeCharacters(char* s, int k) {
    int count[3] = {0, 0, 0};
    for (char* p = s; *p; ++p) {
        count[*p - 'a']++;
    }
    if (count[0] < k || count[1] < k || count[2] < k) {
        return -1;
    }

    int n = 0;
    while (s[n]) {
        n++;
    }

    int left_count[3] = {0, 0, 0};
    int right_count[3] = {count[0], count[1], count[2]};
    int min_minutes = n + 1;

    for (int left = 0; left <= n; ++left) {
        while (right_count[0] >= k && right_count[1] >= k && right_count[2] >= k) {
            int minutes = left + (n - (n - right_count[0] - right_count[1] - right_count[2]));
            if (minutes < min_minutes) {
                min_minutes = minutes;
            }
            right_count[s[n - right_count[0] - right_count[1] - right_count[2]] - 'a']++;
        }
        if (left < n) {
            left_count[s[left] - 'a']++;
            right_count[s[left] - 'a']--;
        }
    }

    return min_minutes;     
}
