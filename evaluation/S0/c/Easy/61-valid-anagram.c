// Source: https://leetcode.com/problems/valid-anagram/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and t, return true if t is an anagram of s, and false otherwise.
//
// Example:
// Input: s = "anagram", t = "nagaram"
//
// Output: true
//
// Constraints:
// 1 <= s.length, t.length <= 5 * 104
// 	s and t consist of lowercase English letters.
//
//
//  
// Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?
//

bool isAnagram(char* s, char* t) {
    int count[26] = {0};
    while (*s) {
        count[*s - 'a']++;
        s++;
    }
    while (*t) {
        count[*t - 'a']--;
        t++;
    }
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) {
            return false;
        }
    }
    return true;        
}
