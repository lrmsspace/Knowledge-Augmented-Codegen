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

bool repeatedSubstringPattern(char* s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }

    for (int subLen = 1; subLen <= len / 2; subLen++) {
        if (len % subLen == 0) {
            bool match = true;
            for (int i = subLen; i < len; i++) {
                if (s[i] != s[i % subLen]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
    }
    return false;       
}
