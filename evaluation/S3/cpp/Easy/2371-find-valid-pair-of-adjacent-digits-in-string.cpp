// Source: https://leetcode.com/problems/find-valid-pair-of-adjacent-digits-in-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting only of digits. A valid pair is defined as two adjacent digits in s such that:
//
//
// 	The first digit is not equal to the second.
// 	Each digit in the pair appears in s exactly as many times as its numeric value.
//
//
// Return the first valid pair found in the string s when traversing from left to right. If no valid pair exists, return an empty string.
//
// Example:
// Input: s = "2523533"
//
// Output: "23"
//
// Explanation:
//
// Digit '2' appears 2 times and digit '3' appears 3 times. Each digit in the pair "23" appears in s exactly as many times as its numeric value. Hence, the output is "23".
//
// Constraints:
// 2 <= s.length <= 100
// 	s only consists of digits from '1' to '9'.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string findValidPair(string s) {
        int count[10] = {0}; // Count occurrences of digits '1' to '9'

        // Count the occurrences of each digit in the string
        for (char c : s) {
            count[c - '0']++;
        }

        // Traverse the string to find the first valid pair
        for (size_t i = 0; i < s.size() - 1; ++i) {
            char first = s[i];
            char second = s[i + 1];

            if (first != second && count[first - '0'] == first - '0' && count[second - '0'] == second - '0') {
                return string() + first + second; // Return the valid pair as a string
            }
        }

        return ""; // Return an empty string if no valid pair is found          
    }
};
