// Source: https://leetcode.com/problems/remove-invalid-parentheses/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.
//
// Return a list of unique strings that are valid with the minimum number of removals. You may return the answer in any order.
//
// Example:
// Input: s = "()())()"
// Output: ["(())()","()()()"]
//
// Constraints:
// 1 <= s.length <= 25
// 	s consists of lowercase English letters and parentheses '(' and ')'.
// 	There will be at most 20 parentheses in s.
//

class Solution {
    public List<String> removeInvalidParentheses(String s) {
        Set<String> result = new HashSet<>();
        int leftToRemove = 0, rightToRemove = 0;

        for (char c : s.toCharArray()) {
            if (c == '(') {
                leftToRemove++;
            } else if (c == ')') {
                if (leftToRemove > 0) {
                    leftToRemove--;
                } else {
                    rightToRemove++;
                }
            }
        }

        backtrack(s, 0, leftToRemove, rightToRemove, result);
        return new ArrayList<>(result);         
    }
}
