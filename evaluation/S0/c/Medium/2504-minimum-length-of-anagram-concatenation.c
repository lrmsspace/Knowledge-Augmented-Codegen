// Source: https://leetcode.com/problems/minimum-length-of-anagram-concatenation/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s, which is known to be a concatenation of anagrams of some string t.
//
// Return the minimum possible length of the string t.
//
// An anagram is formed by rearranging the letters of a string. For example, "aab", "aba", and, "baa" are anagrams of "aab".
//
// Example:
// Input: s = "abba"
//
// Output: 2
//
// Explanation:
//
// One possible string t could be "ba".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consist only of lowercase English letters.
//

int minAnagramLength(char* s) {
    int freq[26] = {0};
    for (int i = 0; s[i] != '\0'; i++) {
        freq[s[i] - 'a']++;
    }

    int length = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] % 2 != 0) {
            return -1; // Invalid case, cannot form anagrams
        }
        length += freq[i] / 2;
    }

    return length;      
}
