// Source: https://leetcode.com/problems/repeated-substring-pattern/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.
//
// Example:
// Input: s = "abab"
// Output: true
// Explanation: It is the substring "ab" twice.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of lowercase English letters.
//

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int n = s.size();
        for (int len = 1; len <= n / 2; ++len) {
            if (n % len == 0) {
                string substring = s.substr(0, len);
                string constructed;
                for (int i = 0; i < n / len; ++i) {
                    constructed += substring;
                }
                if (constructed == s) {
                    return true;
                }
            }
        }
        return false;           
    }
};
