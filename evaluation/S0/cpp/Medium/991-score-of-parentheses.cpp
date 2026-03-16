// Source: https://leetcode.com/problems/score-of-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// Given a balanced parentheses string s, return the score of the string.
//
// The score of a balanced parentheses string is based on the following rule:
//
//
// 	"()" has score 1.
// 	AB has score A + B, where A and B are balanced parentheses strings.
// 	(A) has score 2 * A, where A is a balanced parentheses string.
//
// Example:
// Input: s = "()"
// Output: 1
//
// Constraints:
// 2 <= s.length <= 50
// 	s consists of only '(' and ')'.
// 	s is a balanced parentheses string.
//

class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> stk;
        stk.push(0); // Initialize with a base score of 0

        for (char c : s) {
            if (c == '(') {
                stk.push(0); // Start a new score context
            } else {
                int v = stk.top();
                stk.pop();
                int w = stk.top();
                stk.pop();
                int score = max(2 * v, 1); // Calculate score for the current pair
                stk.push(w + score); // Add to the previous context
            }
        }

        return stk.top(); // Final score            
    }
};
