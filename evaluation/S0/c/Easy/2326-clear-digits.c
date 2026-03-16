// Source: https://leetcode.com/problems/clear-digits/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s.
//
// Your task is to remove all digits by doing this operation repeatedly:
//
//
// 	Delete the first digit and the closest non-digit character to its left.
//
//
// Return the resulting string after removing all digits.
//
// Note that the operation cannot be performed on a digit that does not have any non-digit character to its left.
//
// Example:
// Input: s = "abc"
//
// Output: "abc"
//
// Explanation:
//
// There is no digit in the string.
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists only of lowercase English letters and digits.
// 	The input is generated such that it is possible to delete all digits.
//

char* clearDigits(char* s) {
    char stack[101];
    int top = -1;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            if (top >= 0) {
                top--; // Remove the closest non-digit character to the left
            }
        } else {
            stack[++top] = s[i]; // Push non-digit character onto the stack
        }
    }
    stack[top + 1] = '\0'; // Null-terminate the resulting string
    // Copy the result back to s
    for (int i = 0; i <= top; i++) {
        s[i] = stack[i];
    }
    s[top + 1] = '\0';
    return s;       
}
