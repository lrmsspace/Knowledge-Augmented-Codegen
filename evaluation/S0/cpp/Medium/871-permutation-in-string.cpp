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

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int> count1(26, 0), count2(26, 0);
        for (char c : s1) {
            count1[c - 'a']++;
        }

        int len1 = s1.length(), len2 = s2.length();
        for (int i = 0; i < len2; ++i) {
            count2[s2[i] - 'a']++;
            if (i >= len1) {
                count2[s2[i - len1] - 'a']--;
            }
            if (count1 == count2) {
                return true;
            }
        }
        return false;           
    }
};
