// Source: https://leetcode.com/problems/count-substrings-with-k-frequency-characters-i/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an integer k, return the total number of substrings of s where at least one character appears at least k times.
//
// Example:
// Input: s = "abacb", k = 2
//
// Output: 4
//
// Explanation:
//
// The valid substrings are:
//
//
// 	"aba" (character 'a' appears 2 times).
// 	"abac" (character 'a' appears 2 times).
// 	"abacb" (character 'a' appears 2 times).
// 	"bacb" (character 'b' appears 2 times).
//
// Constraints:
// 1 <= s.length <= 3000
// 	1 <= k <= s.length
// 	s consists only of lowercase English letters.
//

int numberOfSubstrings(char* s, int k) {
    int n = strlen(s);
    int result = 0;

    for (int i = 0; i < n; i++) {
        int freq[26] = {0};
        for (int j = i; j < n; j++) {
            freq[s[j] - 'a']++;
            if (freq[s[j] - 'a'] == k) {
                result += (n - j);
                break;
            }
        }
    }

    return result;      
}
