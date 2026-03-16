// Source: https://leetcode.com/problems/valid-parentheses/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
//
// An input string is valid if:
//
//
// 	Open brackets must be closed by the same type of brackets.
// 	Open brackets must be closed in the correct order.
// 	Every close bracket has a corresponding open bracket of the same type.
//
// Example:
// Input: s = "()"
//
// Output: true
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of parentheses only '()[]{}'.
//

bool isValid(char* s) {
    char stack[10000];
    int top = -1;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } else {
            if (top == -1) return false;
            char open = stack[top--];
            if ((c == ')' && open != '(') ||
                (c == '}' && open != '{') ||
                (c == ']' && open != '[')) {
                return false;
            }
        }
    }
    return top == -1;       
}
