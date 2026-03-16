// Source: https://leetcode.com/problems/second-largest-digit-in-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given an alphanumeric string s, return the second largest numerical digit that appears in s, or -1 if it does not exist.
//
// An alphanumeric string is a string consisting of lowercase English letters and digits.
//
// Example:
// Input: s = "dfa12321afd"
// Output: 2
// Explanation: The digits that appear in s are [1, 2, 3]. The second largest digit is 2.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of only lowercase English letters and digits.
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
    int secondHighest(string s) {
        int largest = -1, secondLargest = -1;

        for (char c : s) {
            if (isdigit(c)) {
                int digit = c - '0';
                if (digit > largest) {
                    secondLargest = largest;
                    largest = digit;
                } else if (digit > secondLargest && digit < largest) {
                    secondLargest = digit;
                }
            }
        }

        return secondLargest;           
    }
};
