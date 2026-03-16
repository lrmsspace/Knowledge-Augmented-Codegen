// Source: https://leetcode.com/problems/backspace-string-compare/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and t, return true if they are equal when both are typed into empty text editors. '#' means a backspace character.
//
// Note that after backspacing an empty text, the text will continue empty.
//
// Example:
// Input: s = "ab#c", t = "ad#c"
// Output: true
// Explanation: Both s and t become "ac".
//
// Constraints:
// 1 <= s.length, t.length <= 200
// 	s and t only contain lowercase letters and '#' characters.
//
//
//  
// Follow up: Can you solve it in O(n) time and O(1) space?
//

class Solution {
    public boolean backspaceCompare(String s, String t) {
        return build(s).equals(build(t));           
    }
}
