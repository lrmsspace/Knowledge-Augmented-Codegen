// Source: https://leetcode.com/problems/match-substring-after-replacement/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings s and sub. You are also given a 2D character array mappings where mappings[i] = [oldi, newi] indicates that you may perform the following operation any number of times:
//
//
// 	Replace a character oldi of sub with newi.
//
//
// Each character in sub cannot be replaced more than once.
//
// Return true if it is possible to make sub a substring of s by replacing zero or more characters according to mappings. Otherwise, return false.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: s = "fool3e7bar", sub = "leet", mappings = [["e","3"],["t","7"],["t","8"]]
// Output: true
// Explanation: Replace the first 'e' in sub with '3' and 't' in sub with '7'.
// Now sub = "l3e7" is a substring of s, so we return true.
//
// Constraints:
// 1 <= sub.length <= s.length <= 5000
// 	0 <= mappings.length <= 1000
// 	mappings[i].length == 2
// 	oldi != newi
// 	s and sub consist of uppercase and lowercase English letters and digits.
// 	oldi and newi are either uppercase or lowercase English letters or digits.
//

bool matchReplacement(char* s, char* sub, char** mappings, int mappingsSize, int* mappingsColSize) {
    int sLen = strlen(s);
    int subLen = strlen(sub);
    bool map[128][128];
    memset(map, 0, sizeof(map));
    for (int i = 0; i < mappingsSize; i++) {
        char oldc = mappings[i][0];
        char newc = mappings[i][1];
        map[(int)oldc][(int)newc] = true;
    }

    for (int i = 0; i <= sLen - subLen; i++) {
        bool match = true;
        for (int j = 0; j < subLen; j++) {
            char sc = s[i + j];
            char subc = sub[j];
            if (sc != subc && !map[(int)subc][(int)sc]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;       
}
