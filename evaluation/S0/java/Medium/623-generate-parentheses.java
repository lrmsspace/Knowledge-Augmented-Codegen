// Source: https://leetcode.com/problems/generate-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
//
// Example:
// Input: n = 3
// Output: ["((()))","(()())","(())()","()(())","()()()"]
//
// Constraints:
// 1 <= n <= 8
//

class Solution {
    public List<String> generateParenthesis(int n) {
        List<String> result = new ArrayList<>();
        backtrack(result, "", 0, 0, n);
        return result;          
    }
}
