// Source: https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/   |   Difficulty: Medium
//
// Problem Description:
// A string s is called good if there are no two different characters in s that have the same frequency.
//
// Given a string s, return the minimum number of characters you need to delete to make s good.
//
// The frequency of a character in a string is the number of times it appears in the string. For example, in the string "aab", the frequency of 'a' is 2, while the frequency of 'b' is 1.
//
// Example:
// Input: s = "aab"
// Output: 0
// Explanation: s is already good.
//
// Constraints:
// 1 <= s.length <= 105
// 	s contains only lowercase English letters.
//

int minDeletions(char* s) {
    int freq[26] = {0};
    for (int i = 0; s[i]; i++) {
        freq[s[i] - 'a']++;
    }

    int deletions = 0;
    int usedFreq[100001] = {0};

    for (int i = 0; i < 26; i++) {
        while (freq[i] > 0 && usedFreq[freq[i]]) {
            freq[i]--;
            deletions++;
        }
        if (freq[i] > 0) {
            usedFreq[freq[i]] = 1;
        }
    }

    return deletions;       
}
