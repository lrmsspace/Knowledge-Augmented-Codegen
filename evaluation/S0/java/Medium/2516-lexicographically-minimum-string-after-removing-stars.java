// Source: https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s. It may contain any number of '*' characters. Your task is to remove all '*' characters.
//
// While there is a '*', do the following operation:
//
//
// 	Delete the leftmost '*' and the smallest non-'*' character to its left. If there are several smallest characters, you can delete any of them.
//
//
// Return the lexicographically smallest resulting string after removing all '*' characters.
//
// Example:
// Input: s = "aaba*"
//
// Output: "aab"
//
// Explanation:
//
// We should delete one of the 'a' characters with '*'. If we choose s[3], s becomes the lexicographically smallest.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters and '*'.
// 	The input is generated such that it is possible to delete all '*' characters.
//

class Solution {
    public String clearStars(String s) {
        StringBuilder sb = new StringBuilder();
        int starCount = 0;

        for (char c : s.toCharArray()) {
            if (c == '*') {
                starCount++;
            } else {
                if (starCount > 0) {
                    starCount--;
                } else {
                    sb.append(c);
                }
            }
        }

        return sb.toString();           
    }
}
