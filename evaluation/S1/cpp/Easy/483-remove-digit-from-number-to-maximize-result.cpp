// Source: https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string number representing a positive integer and a character digit.
//
// Return the resulting string after removing exactly one occurrence of digit from number such that the value of the resulting string in decimal form is maximized. The test cases are generated such that digit occurs at least once in number.
//
// Example:
// Input: number = "123", digit = "3"
// Output: "12"
// Explanation: There is only one '3' in "123". After removing '3', the result is "12".
//
// Constraints:
// 2 <= number.length <= 100
// 	number consists of digits from '1' to '9'.
// 	digit is a digit from '1' to '9'.
// 	digit occurs at least once in number.
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
    string removeDigit(string number, char digit) {
        string maxNumber;
        for (size_t i = 0; i < number.size(); ++i) {
            if (number[i] == digit) {
                string candidate = number.substr(0, i) + number.substr(i + 1);
                if (candidate > maxNumber) {
                    maxNumber = candidate;
                }
            }
        }
        return maxNumber;           
    }
};
