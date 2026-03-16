// Source: https://leetcode.com/problems/reformat-the-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given an alphanumeric string s. (Alphanumeric string is a string consisting of lowercase English letters and digits).
//
// You have to find a permutation of the string where no letter is followed by another letter and no digit is followed by another digit. That is, no two adjacent characters have the same type.
//
// Return the reformatted string or return an empty string if it is impossible to reformat the string.
//
// Example:
// Input: s = "a0b1c2"
// Output: "0a1b2c"
// Explanation: No two adjacent characters have the same type in "0a1b2c". "a0b1c2", "0a1b2c", "0c2a1b" are also valid permutations.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of only lowercase English letters and/or digits.
//

class Solution {
    public String reformat(String s) {
        StringBuilder letters = new StringBuilder();
        StringBuilder digits = new StringBuilder();

        for (char c : s.toCharArray()) {
            if (Character.isLetter(c)) {
                letters.append(c);
            } else {
                digits.append(c);
            }
        }

        if (Math.abs(letters.length() - digits.length()) > 1) {
            return "";
        }

        StringBuilder result = new StringBuilder();
        StringBuilder longer = letters.length() >= digits.length() ? letters : digits;
        StringBuilder shorter = letters.length() < digits.length() ? letters : digits;

        for (int i = 0; i < shorter.length(); i++) {
            result.append(longer.charAt(i));
            result.append(shorter.charAt(i));
        }

        if (longer.length() > shorter.length()) {
            result.append(longer.charAt(longer.length() - 1));
        }

        return result.toString();           
    }
}
