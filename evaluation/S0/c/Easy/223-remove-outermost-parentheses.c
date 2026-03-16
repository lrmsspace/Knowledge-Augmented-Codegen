// Source: https://leetcode.com/problems/remove-outermost-parentheses/   |   Difficulty: Easy
//
// Problem Description:
// A valid parentheses string is either empty "", "(" + A + ")", or A + B, where A and B are valid parentheses strings, and + represents string concatenation.
//
//
// 	For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.
//
//
// A valid parentheses string s is primitive if it is nonempty, and there does not exist a way to split it into s = A + B, with A and B nonempty valid parentheses strings.
//
// Given a valid parentheses string s, consider its primitive decomposition: s = P1 + P2 + ... + Pk, where Pi are primitive valid parentheses strings.
//
// Return s after removing the outermost parentheses of every primitive string in the primitive decomposition of s.
//
// Example:
// Input: s = "(()())(())"
// Output: "()()()"
// Explanation: 
// The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
// After removing outer parentheses of each part, this is "()()" + "()" = "()()()".
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '(' or ')'.
// 	s is a valid parentheses string.
//

char* removeOuterParentheses(char* s) {
    int len = strlen(s);
    char* result = (char*)malloc(len + 1);
    int index = 0;
    int balance = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            if (balance > 0) {
                result[index++] = s[i];
            }
            balance++;
        } else {
            balance--;
            if (balance > 0) {
                result[index++] = s[i];
            }
        }
    }

    result[index] = '\0';
    return result;      
}
