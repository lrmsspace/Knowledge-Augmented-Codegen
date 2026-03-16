// Source: https://leetcode.com/problems/make-three-strings-equal/   |   Difficulty: Easy
//
// Problem Description:
// You are given three strings: s1, s2, and s3. In one operation you can choose one of these strings and delete its rightmost character. Note that you cannot completely empty a string.
//
// Return the minimum number of operations required to make the strings equal. If it is impossible to make them equal, return -1.
//
// Example:
// Input: s1 = "abc", s2 = "abb", s3 = "ab"
//
// Output: 2
//
// Explanation: Deleting the rightmost character from both s1 and s2 will result in three equal strings.
//
// Constraints:
// 1 <= s1.length, s2.length, s3.length <= 100
// 	s1, s2 and s3 consist only of lowercase English letters.
//

class Solution {
    public int findMinimumOperations(String s1, String s2, String s3) {
        int i = s1.length() - 1;
        int j = s2.length() - 1;
        int k = s3.length() - 1;

        while (i >= 0 && j >= 0 && k >= 0) {
            if (s1.charAt(i) == s2.charAt(j) && s2.charAt(j) == s3.charAt(k)) {
                break;
            }
            if (s1.charAt(i) >= s2.charAt(j) && s1.charAt(i) >= s3.charAt(k)) {
                i--;
            } else if (s2.charAt(j) >= s1.charAt(i) && s2.charAt(j) >= s3.charAt(k)) {
                j--;
            } else {
                k--;
            }
        }

        if (i < 0 || j < 0 || k < 0) {
            return -1;
        }

        return (s1.length() - 1 - i) + (s2.length() - 1 - j) + (s3.length() - 1 - k);           
    }
}
