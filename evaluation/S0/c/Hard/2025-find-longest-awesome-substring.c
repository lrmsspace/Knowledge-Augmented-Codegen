// Source: https://leetcode.com/problems/find-longest-awesome-substring/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s. An awesome substring is a non-empty substring of s such that we can make any number of swaps in order to make it a palindrome.
//
// Return the length of the maximum length awesome substring of s.
//
// Example:
// Input: s = "3242415"
// Output: 5
// Explanation: "24241" is the longest awesome substring, we can form the palindrome "24142" with some swaps.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of digits.
//

int longestAwesome(char* s) {
    int n = strlen(s);
    int pos[1024];
    for (int i = 0; i < 1024; i++) pos[i] = -1;
    pos[0] = 0;
    int state = 0, maxLen = 1;
    for (int i = 0; i < n; i++) {
        int digit = s[i] - '0';
        state ^= (1 << digit);
        if (pos[state] >= 0) {
            int len = i + 1 - pos[state];
            if (len > maxLen) maxLen = len;
        } else {
            pos[state] = i + 1;
        }
        for (int d = 0; d < 10; d++) {
            int toggledState = state ^ (1 << d);
            if (pos[toggledState] >= 0) {
                int len = i + 1 - pos[toggledState];
                if (len > maxLen) maxLen = len;
            }
        }
    }
    return maxLen;      
}
