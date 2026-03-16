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

int scoreOfParentheses(char* s) {
    int score = 0;
    int depth = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            depth++;
        } else {
            depth--;
            if (s[i - 1] == '(') {
                score += 1 << depth; // Equivalent to pow(2, depth)
            }
        }
    }

    return score;       
}
