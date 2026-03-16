// Source: https://leetcode.com/problems/permutation-in-string/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
//
// In other words, return true if one of s1's permutations is the substring of s2.
//
// Example:
// Input: s1 = "ab", s2 = "eidbaooo"
// Output: true
// Explanation: s2 contains one permutation of s1 ("ba").
//
// Constraints:
// 1 <= s1.length, s2.length <= 104
// 	s1 and s2 consist of lowercase English letters.
//

bool checkInclusion(char* s1, char* s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 > len2) return false;

    int count1[26] = {0};
    int count2[26] = {0};

    for (int i = 0; i < len1; i++) {
        count1[s1[i] - 'a']++;
        count2[s2[i] - 'a']++;
    }

    int matches = 0;
    for (int i = 0; i < 26; i++) {
        if (count1[i] == count2[i]) {
            matches++;
        }
    }

    for (int i = 0; i < len2 - len1; i++) {
        if (matches == 26) return true;

        int indexOut = s2[i] - 'a';
        int indexIn = s2[i + len1] - 'a';

        count2[indexIn]++;
        if (count2[indexIn] == count1[indexIn]) {
            matches++;
        } else if (count2[indexIn] == count1[indexIn] + 1) {
            matches--;
        }

        count2[indexOut]--;
        if (count2[indexOut] == count1[indexOut]) {
            matches++;
        } else if (count2[indexOut] == count1[indexOut] - 1) {
            matches--;
        }
    }

    return matches == 26;       
}
