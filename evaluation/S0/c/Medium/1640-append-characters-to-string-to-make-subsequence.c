// Source: https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s and t consisting of only lowercase English letters.
//
// Return the minimum number of characters that need to be appended to the end of s so that t becomes a subsequence of s.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// Example:
// Input: s = "coaching", t = "coding"
// Output: 4
// Explanation: Append the characters "ding" to the end of s so that s = "coachingding".
// Now, t is a subsequence of s ("coachingding").
// It can be shown that appending any 3 characters to the end of s will never make t a subsequence.
//
// Constraints:
// 1 <= s.length, t.length <= 105
// 	s and t consist only of lowercase English letters.
//

int appendCharacters(char* s, char* t) {
    int s_len = strlen(s);
    int t_len = strlen(t);
    int i = 0, j = 0;

    while (i < s_len && j < t_len) {
        if (s[i] == t[j]) {
            j++;
        }
        i++;
    }

    return t_len - j;       
}
