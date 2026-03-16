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
    string minRemoveToMakeValid(string s) {
        int n = s.length();
        string res;
        res.reserve(n);
        int balance = 0;
        // First pass: remove invalid ')'
        for (char c : s) {
            if (c == '(') {
                balance++;
                res.push_back(c);
            } else if (c == ')') {
                if (balance > 0) {
                    balance--;
                    res.push_back(c);
                }
            } else {
                res.push_back(c);
            }
        }
        // Second pass: remove invalid '(' from the end
        if (balance == 0) {
            return res;
        }
        string finalRes;
        finalRes.reserve(res.length() - balance);
        for (int i = res.length() - 1; i >= 0; --i) {
            char c = res[i];
            if (c == '(' && balance > 0) {
                balance--;
                continue;
            }
            finalRes.push_back(c);
        }
        reverse(finalRes.begin(), finalRes.end());
        return finalRes;            
    }
};
