// Source: https://leetcode.com/problems/longest-valid-parentheses/   |   Difficulty: Hard
//
// Problem Description:
// Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses substring.
//
// Example:
// Input: s = "(()"
// Output: 2
// Explanation: The longest valid parentheses substring is "()".
//
// Constraints:
// 0 <= s.length <= 3 * 104
// 	s[i] is '(', or ')'.
//

class Solution {
public:
    int longestValidParentheses(string s) {
        int maxLen = 0;
        int left = 0, right = 0;
        
        // Left to right scan
        for (char c : s) {
            if (c == '(') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                maxLen = max(maxLen, 2 * right);
            } else if (right > left) {
                left = right = 0;
            }
        }
        
        left = right = 0;
        // Right to left scan
        for (int i = s.length() - 1; i >= 0; i--) {
            char c = s[i];
            if (c == '(') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                maxLen = max(maxLen, 2 * left);
            } else if (left > right) {
                left = right = 0;
            }
        }
        
        return maxLen;          
    }
};
