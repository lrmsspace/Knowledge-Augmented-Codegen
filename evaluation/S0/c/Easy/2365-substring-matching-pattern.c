// Source: https://leetcode.com/problems/substring-matching-pattern/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s and a pattern string p, where p contains exactly one '*' character.
//
// The '*' in p can be replaced with any sequence of zero or more characters.
//
// Return true if p can be made a substring of s, and false otherwise.
//
// Example:
// Input: s = "leetcode", p = "ee*e"
//
// Output: true
//
// Explanation:
//
// By replacing the '*' with "tcod", the substring "eetcode" matches the pattern.
//
// Constraints:
// 1 <= s.length <= 50
// 	1 <= p.length <= 50 
// 	s contains only lowercase English letters.
// 	p contains only lowercase English letters and exactly one '*'
//

bool hasMatch(char* s, char* p) {
    char* star = strchr(p, '*');
    int prefixLen = star - p;
    int suffixLen = strlen(star + 1);
    int sLen = strlen(s);

    if (sLen < prefixLen + suffixLen) {
        return false;
    }

    // Check prefix
    for (int i = 0; i < prefixLen; i++) {
        if (s[i] != p[i]) {
            return false;
        }
    }

    // Check suffix
    for (int i = 0; i < suffixLen; i++) {
        if (s[sLen - suffixLen + i] != star[1 + i]) {
            return false;
        }
    }

    return true;        
}
