// Source: https://leetcode.com/problems/longest-nice-substring/   |   Difficulty: Easy
//
// Problem Description:
// A string s is nice if, for every letter of the alphabet that s contains, it appears both in uppercase and lowercase. For example, "abABB" is nice because 'A' and 'a' appear, and 'B' and 'b' appear. However, "abA" is not because 'b' appears, but 'B' does not.
//
// Given a string s, return the longest substring of s that is nice. If there are multiple, return the substring of the earliest occurrence. If there are none, return an empty string.
//
// Example:
// Input: s = "YazaAay"
// Output: "aAa"
// Explanation: "aAa" is a nice string because 'A/a' is the only letter of the alphabet in s, and both 'A' and 'a' appear.
// "aAa" is the longest nice substring.
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of uppercase and lowercase English letters.
//

char* longestNiceSubstring(char* s) {
    int n = strlen(s);
    int max_len = 0;
    int start_index = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int lower[26] = {0};
            int upper[26] = {0};
            for (int k = i; k < j; k++) {
                if (s[k] >= 'a' && s[k] <= 'z') {
                    lower[s[k] - 'a'] = 1;
                } else if (s[k] >= 'A' && s[k] <= 'Z') {
                    upper[s[k] - 'A'] = 1;
                }
            }
            int is_nice = 1;
            for (int k = 0; k < 26; k++) {
                if (lower[k] != upper[k]) {
                    is_nice = 0;
                    break;
                }
            }
            if (is_nice && (j - i) > max_len) {
                max_len = j - i;
                start_index = i;
            }
        }
    }

    char* result = (char*)malloc((max_len + 1) * sizeof(char));
    strncpy(result, s + start_index, max_len);
    result[max_len] = '\0';
    return result;      
}
