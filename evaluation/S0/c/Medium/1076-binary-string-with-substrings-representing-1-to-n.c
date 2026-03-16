// Source: https://leetcode.com/problems/binary-string-with-substrings-representing-1-to-n/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s and a positive integer n, return true if the binary representation of all the integers in the range [1, n] are substrings of s, or false otherwise.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "0110", n = 3
// Output: true
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either '0' or '1'.
// 	1 <= n <= 109
//

bool queryString(char* s, int n) {
    int maxLen = 0;
    while ((1 << maxLen) - 1 < n) {
        maxLen++;
    }

    int total = 0;
    for (int len = 1; len <= maxLen; len++) {
        int start = 1 << (len - 1);
        int end = (1 << len) - 1;
        if (end > n) {
            end = n;
        }
        int needed = end - start + 1;
        int found = 0;
        for (int i = 0; i <= (int)strlen(s) - len; i++) {
            if (s[i] == '0') {
                continue;
            }
            int num = 0;
            for (int j = 0; j < len; j++) {
                num = (num << 1) | (s[i + j] - '0');
            }
            if (num >= start && num <= end) {
                found |= (1 << (num - start));
            }
        }
        for (int i = 0; i < needed; i++) {
            if (((found >> i) & 1) == 0) {
                return false;
            }
        }
        total += needed;
    }
    return true;        
}
