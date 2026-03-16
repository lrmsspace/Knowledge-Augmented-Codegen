// Source: https://leetcode.com/problems/number-of-wonderful-substrings/   |   Difficulty: Medium
//
// Problem Description:
// A wonderful string is a string where at most one letter appears an odd number of times.
//
//
// 	For example, "ccjjc" and "abab" are wonderful, but "ab" is not.
//
//
// Given a string word that consists of the first ten lowercase English letters ('a' through 'j'), return the number of wonderful non-empty substrings in word. If the same substring appears multiple times in word, then count each occurrence separately.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: word = "aba"
// Output: 4
// Explanation: The four wonderful substrings are underlined below:
// - "aba" -> "a"
// - "aba" -> "b"
// - "aba" -> "a"
// - "aba" -> "aba"
//
// Constraints:
// 1 <= word.length <= 105
// 	word consists of lowercase English letters from 'a' to 'j'.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {

public:

    long long wonderfulSubstrings(string word) {

        
        // The idea is to use a bitmask to represent the parity of the counts of characters in the current substring.
        // We can use a hash map to count the occurrences of each bitmask. For each character, we toggle the corresponding bit in the bitmask.
        // To count the wonderful substrings, we check how many times we've seen the current bitmask and also how many times we've seen bitmasks that differ by exactly one bit (which would indicate that one character has an odd count).
        
        unordered_map<int, long long> count;
        count[0] = 1; // Base case: empty substring has a bitmask of 0
        int bitmask = 0;
        long long result = 0;

        for (char c : word) {
            int index = c - 'a';
            bitmask ^= (1 << index); // Toggle the bit for the current character
            
            // Count substrings with the same bitmask
            result += count[bitmask];
            
            // Count substrings that differ by one bit
            for (int i = 0; i < 10; ++i) {
                int toggled_bitmask = bitmask ^ (1 << i);
                result += count[toggled_bitmask];
            }
            
            // Increment the count for the current bitmask
            count[bitmask]++;
        }

        return result;
    }

};
