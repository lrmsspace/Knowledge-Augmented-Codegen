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

bool checkValidString(char* s) {
    int low = 0, high = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '(') {
            low++;
            high++;
        } else if (s[i] == ')') {
            low--;
            high--;
        } else { // s[i] == '*'
            low--;
            high++;
        }
        if (high < 0) {
            return false;
        }
        if (low < 0) {
            low = 0;
        }
    }
    return low == 0;        
}
