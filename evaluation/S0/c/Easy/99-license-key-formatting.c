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

char* licenseKeyFormatting(char* s, int k) {
    int len = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] != '-') {
            len++;
        }
    }

    int firstGroupLen = len % k;
    if (firstGroupLen == 0) {
        firstGroupLen = k;
    }

    int totalLen = len + (len - firstGroupLen) / k;
    char* result = (char*)malloc((totalLen + 1) * sizeof(char));
    result[totalLen] = '\0';

    int index = totalLen - 1;
    int count = 0;

    for (int i = strlen(s) - 1; i >= 0; i--) {
        if (s[i] != '-') {
            if (count == k) {
                result[index--] = '-';
                count = 0;
            }
            result[index--] = toupper(s[i]);
            count++;
        }
    }

    return result;      
}
