// Source: https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s that consists of lowercase English letters.
//
// A string is called special if it is made up of only a single character. For example, the string "abc" is not special, whereas the strings "ddd", "zz", and "f" are special.
//
// Return the length of the longest special substring of s which occurs at least thrice, or -1 if no special substring occurs at least thrice.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: s = "aaaa"
// Output: 2
// Explanation: The longest special substring which occurs thrice is "aa": substrings "aaaa", "aaaa", and "aaaa".
// It can be shown that the maximum length achievable is 2.
//
// Constraints:
// 3 <= s.length <= 5 * 105
// 	s consists of only lowercase English letters.
//

int maximumLength(char* s) {
    int count[26] = {0};
    int maxLen = 0;
    int currentLen = 1;
    char prevChar = s[0];

    for (int i = 1; s[i] != '\0'; i++) {
        if (s[i] == prevChar) {
            currentLen++;
        } else {
            if (currentLen >= 3) {
                count[prevChar - 'a'] = currentLen > count[prevChar - 'a'] ? currentLen : count[prevChar - 'a'];
            }
            prevChar = s[i];
            currentLen = 1;
        }
    }

    // Check the last sequence
    if (currentLen >= 3) {
        count[prevChar - 'a'] = currentLen > count[prevChar - 'a'] ? currentLen : count[prevChar - 'a'];
    }

    for (int i = 0; i < 26; i++) {
        if (count[i] > maxLen) {
            maxLen = count[i];
        }
    }

    return maxLen >= 3 ? maxLen : -1;       
}
