// Source: https://leetcode.com/problems/valid-parenthesis-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s containing only three types of characters: '(', ')' and '*', return true if s is valid.
//
// The following rules define a valid string:
//
//
// 	Any left parenthesis '(' must have a corresponding right parenthesis ')'.
// 	Any right parenthesis ')' must have a corresponding left parenthesis '('.
// 	Left parenthesis '(' must go before the corresponding right parenthesis ')'.
// 	'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".
//
// Example:
// Input: s = "()"
// Output: true
//
// Constraints:
// 1 <= s.length <= 100
// 	s[i] is '(', ')' or '*'.
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
    bool checkValidString(string s) {
        stack<int> leftParenStack; // Stack to store indices of '('
        stack<int> starStack;      // Stack to store indices of '*'

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                leftParenStack.push(i);
            } else if (s[i] == '*') {
                starStack.push(i);
            } else { // s[i] == ')'
                if (!leftParenStack.empty()) {
                    leftParenStack.pop();
                } else if (!starStack.empty()) {
                    starStack.pop();
                } else {
                    return false; // No matching '(' or '*' for ')'
                }
            }
        }

        // Now we need to match remaining '(' with '*' if possible
        while (!leftParenStack.empty() && !starStack.empty()) {
            if (leftParenStack.top() < starStack.top()) {
                leftParenStack.pop();
                starStack.pop();
            } else {
                return false; // A '*' cannot match a '(' that comes after it
            }
        }

        return leftParenStack.empty(); // If there are unmatched '(', return false          
    }
};
