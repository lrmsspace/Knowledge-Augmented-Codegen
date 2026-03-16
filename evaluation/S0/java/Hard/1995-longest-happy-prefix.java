// Source: https://leetcode.com/problems/longest-happy-prefix/   |   Difficulty: Hard
//
// Problem Description:
// A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).
//
// Given a string s, return the longest happy prefix of s. Return an empty string "" if no such prefix exists.
//
// Example:
// Input: s = "level"
// Output: "l"
// Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".
//
// Constraints:
// 1 <= s.length <= 105
// 	s contains only lowercase English letters.
//

class Solution {
    public String longestPrefix(String s) {
        int n = s.length();
        int[] lps = new int[n];
        int length = 0; // length of the previous longest prefix suffix
        int i = 1;

        while (i < n) {
            if (s.charAt(i) == s.charAt(length)) {
                length++;
                lps[i] = length;
                i++;
            } else {
                if (length != 0) {
                    length = lps[length - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }

        return s.substring(0, lps[n - 1]);                  
    }
}
