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
    public boolean repeatedSubstringPattern(String s) {
        int n = s.length();
        for (int len = 1; len <= n / 2; len++) {
            if (n % len == 0) {
                String substring = s.substring(0, len);
                StringBuilder sb = new StringBuilder();
                int repeatCount = n / len;
                for (int i = 0; i < repeatCount; i++) {
                    sb.append(substring);
                }
                if (sb.toString().equals(s)) {
                    return true;
                }
            }
        }
        return false;
        
    }
}
