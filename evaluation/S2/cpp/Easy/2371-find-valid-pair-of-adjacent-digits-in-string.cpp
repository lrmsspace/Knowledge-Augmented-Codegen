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
// - N/A
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
        // Count the frequency of each digit in the string
        int freq[10] = {0};
        for (char c : s) {
            freq[c - '0']++;
        }

        // Check for valid pairs of adjacent digits
        for (size_t i = 0; i < s.size() - 1; ++i) {
            char first = s[i];
            char second = s[i + 1];

            if (first != second && freq[first - '0'] == first - '0' && freq[second - '0'] == second - '0') {
                return string(1, first) + second; // Return the valid pair as a string
            }
        }

        return ""; // Return an empty string if no valid pair is found          
    }
};
