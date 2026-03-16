// Source: https://leetcode.com/problems/string-to-integer-atoi/   |   Difficulty: Medium
//
// Problem Description:
// Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer.
//
// The algorithm for myAtoi(string s) is as follows:
//
//
// 	Whitespace: Ignore any leading whitespace (" ").
// 	Signedness: Determine the sign by checking if the next character is '-' or '+', assuming positivity if neither present.
// 	Conversion: Read the integer by skipping leading zeros until a non-digit character is encountered or the end of the string is reached. If no digits were read, then the result is 0.
// 	Rounding: If the integer is out of the 32-bit signed integer range [-231, 231 - 1], then round the integer to remain in the range. Specifically, integers less than -231 should be rounded to -231, and integers greater than 231 - 1 should be rounded to 231 - 1.
//
//
// Return the integer as the final result.
//
// Example:
// Input: s = "42"
//
// Output: 42
//
// Explanation:
//
//
// The underlined characters are what is read in and the caret is the current reader position.
// Step 1: "42" (no characters read because there is no leading whitespace)
//          ^
// Step 2: "42" (no characters read because there is neither a '-' nor '+')
//          ^
// Step 3: "42" ("42" is read in)
//            ^
//
// Constraints:
// 0 <= s.length <= 200
// 	s consists of English letters (lower-case and upper-case), digits (0-9), ' ', '+', '-', and '.'.
//

int myAtoi(char* s) {
    int i = 0;
    int sign = 1;
    long result = 0;

    // Skip leading whitespace
    while (s[i] == ' ') {
        i++;
    }

    // Check for sign
    if (s[i] == '+' || s[i] == '-') {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    // Convert digits to integer
    while (s[i] >= '0' && s[i] <= '9') {
        result = result * 10 + (s[i] - '0');

        // Check for overflow
        if (sign == 1 && result > INT32_MAX) {
            return INT32_MAX;
        } else if (sign == -1 && -result < INT32_MIN) {
            return INT32_MIN;
        }

        i++;
    }

    return (int)(sign * result);        
}
