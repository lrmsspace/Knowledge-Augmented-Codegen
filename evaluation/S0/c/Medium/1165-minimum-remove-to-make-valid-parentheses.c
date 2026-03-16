// Source: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s of '(' , ')' and lowercase English characters.
//
// Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.
//
// Formally, a parentheses string is valid if and only if:
//
//
// 	It is the empty string, contains only lowercase characters, or
// 	It can be written as AB (A concatenated with B), where A and B are valid strings, or
// 	It can be written as (A), where A is a valid string.
//
// Example:
// Input: s = "lee(t(c)o)de)"
// Output: "lee(t(c)o)de"
// Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '(' , ')', or lowercase English letter.
//

char* minRemoveToMakeValid(char* s) {
    int len = strlen(s);
    int* stack = (int*)malloc(len * sizeof(int));
    int top = -1;

    // First pass: Identify unmatched parentheses
    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            stack[++top] = i; // Push index of '(' onto stack
        } else if (s[i] == ')') {
            if (top >= 0) {
                top--; // Pop matching '(' from stack
            } else {
                stack[++top] = i; // Push index of unmatched ')' onto stack
            }
        }
    }

    // Mark unmatched parentheses for removal
    int* toRemove = (int*)calloc(len, sizeof(int));
    for (int i = 0; i <= top; i++) {
        toRemove[stack[i]] = 1;
    }
    free(stack);

    // Second pass: Build the result string
    char* result = (char*)malloc((len - top + 1) * sizeof(char));
    int idx = 0;
    for (int i = 0; i < len; i++) {
        if (!toRemove[i]) {
            result[idx++] = s[i];
        }
    }
    result[idx] = '\0';

    free(toRemove);
    return result;      
}
