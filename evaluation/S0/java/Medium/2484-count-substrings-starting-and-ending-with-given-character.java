// Source: https://leetcode.com/problems/count-substrings-starting-and-ending-with-given-character/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and a character c. Return the total number of substrings of s that start and end with c.
//
// Example:
// Input: s = "abada", c = "a"
//
// Output: 6
//
// Explanation: Substrings starting and ending with "a" are: "abada", "abada", "abada", "abada", "abada", "abada".
//
// Constraints:
// 1 <= s.length <= 105
// 	s and c consist only of lowercase English letters.
//

class Solution {
    public long countSubstrings(String s, char c) {
        long count = 0;
        long result = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == c) {
                count++;
                result += count;
            }
        }

        return result;          
    }
}
