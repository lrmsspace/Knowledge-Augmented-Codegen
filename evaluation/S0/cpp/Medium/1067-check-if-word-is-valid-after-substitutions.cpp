// Source: https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, determine if it is valid.
//
// A string s is valid if, starting with an empty string t = "", you can transform t into s after performing the following operation any number of times:
//
//
// 	Insert string "abc" into any position in t. More formally, t becomes tleft + "abc" + tright, where t == tleft + tright. Note that tleft and tright may be empty.
//
//
// Return true if s is a valid string, otherwise, return false.
//
// Example:
// Input: s = "aabcbc"
// Output: true
// Explanation:
// "" -> "abc" -> "aabcbc"
// Thus, "aabcbc" is valid.
//
// Constraints:
// 1 <= s.length <= 2 * 104
// 	s consists of letters 'a', 'b', and 'c'
//

class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        for (char ch : s) {
            if (ch == 'c') {
                if (stk.size() < 2) return false;
                char b = stk.top(); stk.pop();
                char a = stk.top(); stk.pop();
                if (a != 'a' || b != 'b') return false;
            } else {
                stk.push(ch);
            }
        }
        return stk.empty();         
    }
};
