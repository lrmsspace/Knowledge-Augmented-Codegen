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

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int balance = 0;
        for (char c : s) {
            if (c == '(') {
                balance++;
            } else if (c == ')') {
                if (balance == 0) {
                    c = '*'; // Mark for removal
                } else {
                    balance--;
                }
            }
        }

        // Remove excess '(' from the end
        string result;
        for (int i = s.size() - 1; i >= 0; --i) {
            if (s[i] == '(' && balance > 0) {
                balance--;
            } else if (s[i] != '*') {
                result += s[i];
            }
        }

        reverse(result.begin(), result.end());
        return result;          
    }
};
