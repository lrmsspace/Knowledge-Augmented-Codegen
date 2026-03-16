// Source: https://leetcode.com/problems/ransom-note/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings ransomNote and magazine, return true if ransomNote can be constructed by using the letters from magazine and false otherwise.
//
// Each letter in magazine can only be used once in ransomNote.
//
// Example:
// Input: ransomNote = "a", magazine = "b"
// Output: false
//
// Constraints:
// 1 <= ransomNote.length, magazine.length <= 105
// 	ransomNote and magazine consist of lowercase English letters.
//

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> count(26, 0);
        for (char c : magazine) {
            count[c - 'a']++;
        }
        for (char c : ransomNote) {
            if (--count[c - 'a'] < 0) {
                return false;
            }
        }
        return true;            
    }
};
