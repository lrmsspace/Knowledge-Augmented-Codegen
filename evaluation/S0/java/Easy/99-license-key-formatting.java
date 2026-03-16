// Source: https://leetcode.com/problems/license-key-formatting/   |   Difficulty: Easy
//
// Problem Description:
// You are given a license key represented as a string s that consists of only alphanumeric characters and dashes. The string is separated into n + 1 groups by n dashes. You are also given an integer k.
//
// We want to reformat the string s such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.
//
// Return the reformatted license key.
//
// Example:
// Input: s = "5F3Z-2e-9-w", k = 4
// Output: "5F3Z-2E9W"
// Explanation: The string s has been split into two parts, each part has 4 characters.
// Note that the two extra dashes are not needed and can be removed.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of English letters, digits, and dashes '-'.
// 	1 <= k <= 104
//

class Solution {
    public String licenseKeyFormatting(String s, int k) {
        StringBuilder cleaned = new StringBuilder();
        for (char c : s.toCharArray()) {
            if (c != '-') {
                cleaned.append(Character.toUpperCase(c));
            }
        }

        StringBuilder result = new StringBuilder();
        int firstGroupLength = cleaned.length() % k;
        if (firstGroupLength == 0 && cleaned.length() > 0) {
            firstGroupLength = k;
        }

        int index = 0;
        if (firstGroupLength > 0) {
            result.append(cleaned.substring(0, firstGroupLength));
            index += firstGroupLength;
        }

        while (index < cleaned.length()) {
            if (result.length() > 0) {
                result.append('-');
            }
            result.append(cleaned.substring(index, index + k));
            index += k;
        }

        return result.toString();
        
    }
}
