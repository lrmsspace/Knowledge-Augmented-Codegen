// Source: https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer num. You know that Bob will sneakily remap one of the 10 possible digits (0 to 9) to another digit.
//
// Return the difference between the maximum and minimum values Bob can make by remapping exactly one digit in num.
//
// 	The resulting number after remapping can contain leading zeroes.
//
// Example:
// Input: num = 11891
// Output: 99009
// Explanation: 
// To achieve the maximum value, Bob can remap the digit 1 to the digit 9 to yield 99899.
// To achieve the minimum value, Bob can remap the digit 1 to the digit 0, yielding 890.
// The difference between these two numbers is 99009.
//
// Constraints:
// 1 <= num <= 108
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minMaxDifference(int num) {
        string s = to_string(num);

        // Calculate maximum value
        char toMax = ' ';
        for (char c : s) {
            if (c != '9') {
                toMax = c;
                break;
            }
        }
        string maxStr = s;
        if (toMax != ' ') {
            for (char &c : maxStr) {
                if (c == toMax) {
                    c = '9';
                }
            }
        }
        int maxValue = stoi(maxStr);

        // Calculate minimum value
        char toMin = ' ';
        for (char c : s) {
            if (c != '0' && c != s[0]) {
                toMin = c;
                break;
            }
        }
        string minStr = s;
        if (toMin != ' ') {
            for (char &c : minStr) {
                if (c == toMin) {
                    c = (c == s[0]) ? '1' : '0';
                }
            }
        }
        int minValue = stoi(minStr);

        return maxValue - minValue;         
    }
};
