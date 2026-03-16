// Source: https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings of the same length s and t. In one step you can choose any character of t and replace it with another character.
//
// Return the minimum number of steps to make t an anagram of s.
//
// An Anagram of a string is a string that contains the same characters with a different (or the same) ordering.
//
// Example:
// Input: s = "bab", t = "aba"
// Output: 1
// Explanation: Replace the first 'a' in t with b, t = "bba" which is anagram of s.
//
// Constraints:
// 1 <= s.length <= 5 * 104
// 	s.length == t.length
// 	s and t consist of lowercase English letters only.
//

class Solution {
public:
    int minSteps(string s, string t) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }
        for (char c : t) {
            count[c - 'a']--;
        }

        int steps = 0;
        for (int cnt : count) {
            if (cnt > 0) {
                steps += cnt;
            }
        }
        return steps;           
    }
};
