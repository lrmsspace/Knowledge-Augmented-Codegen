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
    public boolean checkValidString(String s) {
        int low = 0;  // Minimum number of open parentheses
        int high = 0; // Maximum number of open parentheses

        for (char c : s.toCharArray()) {
            if (c == '(') {
                low++;
                high++;
            } else if (c == ')') {
                low = Math.max(low - 1, 0);
                high--;
            } else { // c == '*'
                low = Math.max(low - 1, 0);
                high++;
            }

            // If at any point, the maximum number of open parentheses is negative,
            // it means there are more ')' than '(' which is invalid.
            if (high < 0) {
                return false;
            }
        }

        // If the minimum number of open parentheses is zero,
        // it means we can balance all parentheses.
        return low == 0;            
    }
}
