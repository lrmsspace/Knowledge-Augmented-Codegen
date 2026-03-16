// Source: https://leetcode.com/problems/unique-substrings-in-wraparound-string/   |   Difficulty: Medium
//
// Problem Description:
// We define the string base to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so base will look like this:
//
//
// 	"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
//
//
// Given a string s, return the number of unique non-empty substrings of s are present in base.
//
// Example:
// Input: s = "a"
// Output: 1
// Explanation: Only the substring "a" of s is in base.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
//

int findSubstringInWraproundString(char* s) {
    int count[26] = {0};
    int n = strlen(s);
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        if (i > 0 && (s[i] - s[i - 1] + 26) % 26 == 1) {
            maxLen++;
        } else {
            maxLen = 1;
        }
        int index = s[i] - 'a';
        count[index] = fmax(count[index], maxLen);
    }

    int result = 0;
    for (int i = 0; i < 26; i++) {
        result += count[i];
    }

    return result;      
}
