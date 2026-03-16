// Source: https://leetcode.com/problems/minimum-window-substring/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".
//
// The testcases will be generated such that the answer is unique.
//
// Example:
// Input: s = "ADOBECODEBANC", t = "ABC"
// Output: "BANC"
// Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
//
// Constraints:
// m == s.length
// 	n == t.length
// 	1 <= m, n <= 105
// 	s and t consist of uppercase and lowercase English letters.
//
//
//  
// Follow up: Could you find an algorithm that runs in O(m + n) time?
//

char* minWindow(char* s, char* t) {
    int need[128] = {0}, window[128] = {0};
    int left = 0, right = 0, valid = 0;
    int start = 0, len = __INT_MAX__;
    for (int i = 0; t[i]; i++) {
        need[(unsigned char)t[i]]++;
    }
    while (s[right]) {
        char c = s[right];
        right++;
        if (need[(unsigned char)c] > 0) {
            window[(unsigned char)c]++;
            if (window[(unsigned char)c] == need[(unsigned char)c]) {
                valid++;
            }
        }
        while (valid == 0) {
            if (right - left < len) {
                start = left;
                len = right - left;
            }
            char d = s[left];
            left++;
            if (need[(unsigned char)d] > 0) {
                if (window[(unsigned char)d] == need[(unsigned char)d]) {
                    valid--;
                }
                window[(unsigned char)d]--;
            }
        }
    }
    if (len == __INT_MAX__) return "";
    char *res = (char*)malloc((len + 1) * sizeof(char));
    strncpy(res, s + start, len);
    res[len] = '\0';
    return res;     
}
