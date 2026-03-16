// Source: https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/   |   Difficulty: Easy
//
// Problem Description:
// Given a valid parentheses string s, return the nesting depth of s. The nesting depth is the maximum number of nested parentheses.
//
// Example:
// Input: s = "(1+(2*3)+((8)/4))+1"
//
// Output: 3
//
// Explanation:
//
// Digit 8 is inside of 3 nested parentheses in the string.
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of digits 0-9 and characters '+', '-', '*', '/', '(', and ')'.
// 	It is guaranteed that parentheses expression s is a VPS.
//

int maxDepth(char* s) {
    int current_depth = 0;
    int max_depth = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            current_depth++;
            if (current_depth > max_depth) {
                max_depth = current_depth;
            }
        } else if (s[i] == ')') {
            current_depth--;
        }
    }

    return max_depth;       
}
