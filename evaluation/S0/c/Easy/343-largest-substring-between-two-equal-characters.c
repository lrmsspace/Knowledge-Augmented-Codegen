// Source: https://leetcode.com/problems/largest-substring-between-two-equal-characters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return the length of the longest substring between two equal characters, excluding the two characters. If there is no such substring return -1.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "aa"
// Output: 0
// Explanation: The optimal substring here is an empty substring between the two 'a's.
//
// Constraints:
// 1 <= s.length <= 300
// 	s contains only lowercase English letters.
//

int maxLengthBetweenEqualCharacters(char* s) {
    int maxLen = -1;
    int firstIndex[26];
    for (int i = 0; i < 26; i++) {
        firstIndex[i] = -1;
    }

    for (int i = 0; s[i] != '\0'; i++) {
        int charIndex = s[i] - 'a';
        if (firstIndex[charIndex] == -1) {
            firstIndex[charIndex] = i;
        } else {
            int currentLen = i - firstIndex[charIndex] - 1;
            if (currentLen > maxLen) {
                maxLen = currentLen;
            }
        }
    }

    return maxLen;      
}
