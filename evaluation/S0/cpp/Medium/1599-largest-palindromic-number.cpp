// Source: https://leetcode.com/problems/largest-palindromic-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string num consisting of digits only.
//
// Return the largest palindromic integer (in the form of a string) that can be formed using digits taken from num. It should not contain leading zeroes.
//
// Example:
// Input: num = "444947137"
// Output: "7449447"
// Explanation: 
// Use the digits "4449477" from "444947137" to form the palindromic integer "7449447".
// It can be shown that "7449447" is the largest palindromic integer that can be formed.
//
// Constraints:
// 1 <= num.length <= 105
// 	num consists of digits.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string largestPalindromic(string num) {
        vector<int> count(10, 0);
        for (char c : num) {
            count[c - '0']++;
        }

        string leftHalf = "";
        char middleChar = '\0';

        for (int digit = 9; digit >= 0; --digit) {
            if (count[digit] % 2 == 1 && middleChar == '\0') {
                middleChar = '0' + digit;
            }
            leftHalf += string(count[digit] / 2, '0' + digit);
        }

        // Remove leading zeros from leftHalf
        int nonZeroIndex = 0;
        while (nonZeroIndex < leftHalf.size() && leftHalf[nonZeroIndex] == '0') {
            nonZeroIndex++;
        }
        leftHalf = leftHalf.substr(nonZeroIndex);

        // If leftHalf is empty and we have a middle character, return it
        if (leftHalf.empty() && middleChar != '\0') {
            return string(1, middleChar);
        }

        string rightHalf = leftHalf;
        reverse(rightHalf.begin(), rightHalf.end());

        return leftHalf + (middleChar != '\0' ? string(1, middleChar) : "") + rightHalf;            
    }
};
