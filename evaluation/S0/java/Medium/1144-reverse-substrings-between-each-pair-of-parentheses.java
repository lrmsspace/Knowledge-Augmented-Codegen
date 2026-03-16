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
    public String reverseParentheses(String s) {
        StringBuilder sb = new StringBuilder();
        Deque<Integer> stack = new ArrayDeque<>();

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '(') {
                stack.push(sb.length());
            } else if (c == ')') {
                int start = stack.pop();
                String toReverse = sb.substring(start);
                sb.delete(start, sb.length());
                sb.append(new StringBuilder(toReverse).reverse());
            } else {
                sb.append(c);
            }
        }

        return sb.toString();           
    }
}
