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
    public String minRemoveToMakeValid(String s) {
        StringBuilder sb = new StringBuilder(s);
        int openBrackets = 0;

        // First pass: Remove invalid closing brackets
        for (int i = 0; i < sb.length(); i++) {
            char ch = sb.charAt(i);
            if (ch == '(') {
                openBrackets++;
            } else if (ch == ')') {
                if (openBrackets == 0) {
                    sb.deleteCharAt(i);
                    i--; // Adjust index after deletion
                } else {
                    openBrackets--;
                }
            }
        }

        // Second pass: Remove invalid opening brackets from the end
        for (int i = sb.length() - 1; i >= 0 && openBrackets > 0; i--) {
            if (sb.charAt(i) == '(') {
                sb.deleteCharAt(i);
                openBrackets--;
            }
        }

        return sb.toString();           
    }
}
