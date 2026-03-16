// Source: https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/   |   Difficulty: Easy
//
// Problem Description:
// You are given two strings s1 and s2 of equal length. A string swap is an operation where you choose two indices in a string (not necessarily different) and swap the characters at these indices.
//
// Return true if it is possible to make both strings equal by performing at most one string swap on exactly one of the strings. Otherwise, return false.
//
// Example:
// Input: s1 = "bank", s2 = "kanb"
// Output: true
// Explanation: For example, swap the first character with the last character of s2 to make "bank".
//
// Constraints:
// 1 <= s1.length, s2.length <= 100
// 	s1.length == s2.length
// 	s1 and s2 consist of only lowercase English letters.
//

class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        vector<int> diff;
        for (int i = 0; i < s1.size(); ++i) {
            if (s1[i] != s2[i]) {
                diff.push_back(i);
            }
        }
        if (diff.size() == 0) {
            return true;
        }
        if (diff.size() != 2) {
            return false;
        }
        return s1[diff[0]] == s2[diff[1]] && s1[diff[1]] == s2[diff[0]];            
    }
};
