// Source: https://leetcode.com/problems/valid-number/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, return whether s is a valid number.
//
// For example, all the following are valid numbers: "2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789", while the following are not valid numbers: "abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53".
//
// Formally, a valid number is defined using one of the following definitions:
//
//
// 	An integer number followed by an optional exponent.
// 	A decimal number followed by an optional exponent.
//
//
// An integer number is defined with an optional sign '-' or '+' followed by digits.
//
// A decimal number is defined with an optional sign '-' or '+' followed by one of the following definitions:
//
//
// 	Digits followed by a dot '.'.
// 	Digits followed by a dot '.' followed by digits.
// 	A dot '.' followed by digits.
//
//
// An exponent is defined with an exponent notation 'e' or 'E' followed by an integer number.
//
// The digits are defined as one or more digits.
//
// Example:
// Input: s = "0"
//
// Output: true
//
// Constraints:
// 1 <= s.length <= 20
// 	s consists of only English letters (both uppercase and lowercase), digits (0-9), plus '+', minus '-', or dot '.'.
//

class Solution {
public:
    bool isNumber(string s) {
        int i = 0, n = s.size();
        // Skip leading spaces
        while (i < n && isspace(s[i])) i++;
        
        // Optional sign
        if (i < n && (s[i] == '+' || s[i] == '-')) i++;
        
        bool isNumeric = false;
        // Integer part
        while (i < n && isdigit(s[i])) {
            i++;
            isNumeric = true;
        }
        
        // Decimal part
        if (i < n && s[i] == '.') {
            i++;
            while (i < n && isdigit(s[i])) {
                i++;
                isNumeric = true;
            }
        }
        
        // Exponent part
        if (isNumeric && i < n && (s[i] == 'e' || s[i] == 'E')) {
            i++;
            isNumeric = false;
            // Optional sign after exponent
            if (i < n && (s[i] == '+' || s[i] == '-')) i++;
            while (i < n && isdigit(s[i])) {
                i++;
                isNumeric = true;
            }
        }
        
        // Skip trailing spaces
        while (i < n && isspace(s[i])) i++;
        
        return isNumeric && i == n;         
    }
};
