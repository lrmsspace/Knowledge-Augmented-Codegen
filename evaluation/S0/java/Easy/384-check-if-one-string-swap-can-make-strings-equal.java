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
    public boolean areAlmostEqual(String s1, String s2) {
        int n = s1.length();
        int first = -1, second = -1;
        for (int i = 0; i < n; i++) {
            if (s1.charAt(i) != s2.charAt(i)) {
                if (first == -1) {
                    first = i;
                } else if (second == -1) {
                    second = i;
                } else {
                    return false; // More than two differences
                }
            }
        }

        if (first == -1 && second == -1) {
            return true; // Strings are already equal
        }

        if (second == -1) {
            return false; // Only one difference
        }

        // Check if swapping makes the strings equal
        return s1.charAt(first) == s2.charAt(second) && s1.charAt(second) == s2.charAt(first);          
    }
}
