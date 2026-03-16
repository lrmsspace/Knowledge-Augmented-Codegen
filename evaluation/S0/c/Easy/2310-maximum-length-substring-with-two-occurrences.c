// Source: https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return the maximum length of a substring such that it contains at most two occurrences of each character.
//
// Example:
// Input: s = "bcbbbcba"
//
// Output: 4
//
// Explanation:
// The following substring has a length of 4 and contains at most two occurrences of each character: "bcbbbcba".
//
// Constraints:
// 2 <= s.length <= 100
// 	s consists only of lowercase English letters.
//

int maximumLengthSubstring(char* s) {
    int maxLength = 0;
    int n = strlen(s);

    for (int i = 0; i < n; i++) {
        int count[26] = {0};
        int currentLength = 0;

        for (int j = i; j < n; j++) {
            count[s[j] - 'a']++;
            if (count[s[j] - 'a'] > 2) {
                break;
            }
            currentLength++;
        }

        if (currentLength > maxLength) {
            maxLength = currentLength;
        }
    }

    return maxLength;       
}
