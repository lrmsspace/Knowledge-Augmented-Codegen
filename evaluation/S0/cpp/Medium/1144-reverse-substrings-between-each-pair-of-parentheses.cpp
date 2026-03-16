// Source: https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s that consists of lower case English letters and brackets.
//
// Reverse the strings in each pair of matching parentheses, starting from the innermost one.
//
// Your result should not contain any brackets.
//
// Example:
// Input: s = "(abcd)"
// Output: "dcba"
//
// Constraints:
// 1 <= s.length <= 2000
// 	s only contains lower case English characters and parentheses.
// 	It is guaranteed that all parentheses are balanced.
//

class Solution {
public:
    string reverseParentheses(string s) {
        stack<int> openParenIndices;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                openParenIndices.push(i);
            } else if (s[i] == ')') {
                int openIndex = openParenIndices.top();
                openParenIndices.pop();
                reverse(s.begin() + openIndex + 1, s.begin() + i);
            }
        }

        string result;
        for (char c : s) {
            if (c != '(' && c != ')') {
                result += c;
            }
        }
        return result;          
    }
};
