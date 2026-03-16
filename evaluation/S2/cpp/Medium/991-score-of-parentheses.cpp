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
    int scoreOfParentheses(string s) {
        stack<int> st;
        for (char c : s) {
            if (c == '(') {
                st.push(0); // Push a marker for a new group
            } else {
                int score = 0;
                while (!st.empty() && st.top() != 0) {
                    score += st.top();
                    st.pop();
                }
                st.pop(); // Pop the marker
                st.push(max(2 * score, 1)); // Push the score for the current group
            }
        }

        int totalScore = 0;
        while (!st.empty()) {
            totalScore += st.top();
            st.pop();
        }
        return totalScore;          
    }
};
