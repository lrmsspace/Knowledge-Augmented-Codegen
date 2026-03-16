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

class Solution {
public:
    bool checkValidString(string s) {
        int low = 0, high = 0;
        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            } else if (c == ')') {
                low = max(low - 1, 0);
                high--;
            } else { // c == '*'
                low = max(low - 1, 0);
                high++;
            }
            if (high < 0) {
                return false;
            }
        }
        return low == 0;            
    }
};
