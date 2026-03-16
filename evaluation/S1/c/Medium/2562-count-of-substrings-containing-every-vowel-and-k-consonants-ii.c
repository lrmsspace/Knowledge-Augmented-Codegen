// Source: https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word and a non-negative integer k.
//
// Return the total number of substrings of word that contain every vowel ('a', 'e', 'i', 'o', and 'u') at least once and exactly k consonants.
//
// Example:
// Input: word = "aeioqq", k = 1
//
// Output: 0
//
// Explanation:
//
// There is no substring with every vowel.
//
// Constraints:
// 5 <= word.length <= 2 * 105
//  word consists only of lowercase English letters.
//  0 <= k <= word.length - 5
//
// Helpful references (internal KB):
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
//   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
//   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
//   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
//   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long countOfSubstrings(char* word, int k) {
    int n = strlen(word);
    int vowelCount[5] = {0}; // a, e, i, o, u
    int totalVowels = 0;
    long long result = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        char ch = word[right];
        if (ch == 'a') {
            if (vowelCount[0] == 0) totalVowels++;
            vowelCount[0]++;
        } else if (ch == 'e') {
            if (vowelCount[1] == 0) totalVowels++;
            vowelCount[1]++;
        } else if (ch == 'i') {
            if (vowelCount[2] == 0) totalVowels++;
            vowelCount[2]++;
        } else if (ch == 'o') {
            if (vowelCount[3] == 0) totalVowels++;
            vowelCount[3]++;
        } else if (ch == 'u') {
            if (vowelCount[4] == 0) totalVowels++;
            vowelCount[4]++;
        }

        while ((right - left + 1) - (vowelCount[0] + vowelCount[1] + vowelCount[2] + vowelCount[3] + vowelCount[4]) > k) {
            char leftCh = word[left];
            if (leftCh == 'a') {
                vowelCount[0]--;
                if (vowelCount[0] == 0) totalVowels--;
            } else if (leftCh == 'e') {
                vowelCount[1]--;
                if (vowelCount[1] == 0) totalVowels--;
            } else if (leftCh == 'i') {
                vowelCount[2]--;
                if (vowelCount[2] == 0) totalVowels--;
            } else if (leftCh == 'o') {
                vowelCount[3]--;
                if (vowelCount[3] == 0) totalVowels--;
            } else if (leftCh == 'u') {
                vowelCount[4]--;
                if (vowelCount[4] == 0) totalVowels--;
            }
            left++;
        }

        if (totalVowels == 5 && (right - left + 1) - (vowelCount[0] + vowelCount[1] + vowelCount[2] + vowelCount[3] + vowelCount[4]) == k) {
            result += 1;
            int tempLeft = left;
            while (tempLeft < right && !(word[tempLeft] == 'a' || word[tempLeft] == 'e' || word[tempLeft] == 'i' || word[tempLeft] == 'o' || word[tempLeft] == 'u')) {
                result += 1;
                tempLeft++;
            }
        }
    }
    return result;
}
