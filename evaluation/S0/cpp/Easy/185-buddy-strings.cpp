// Source: https://leetcode.com/problems/buddy-strings/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and goal, return true if you can swap two letters in s so the result is equal to goal, otherwise, return false.
//
// Swapping letters is defined as taking two indices i and j (0-indexed) such that i != j and swapping the characters at s[i] and s[j].
//
//
// 	For example, swapping at indices 0 and 2 in "abcd" results in "cbad".
//
// Example:
// Input: s = "ab", goal = "ba"
// Output: true
// Explanation: You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is equal to goal.
//
// Constraints:
// 1 <= s.length, goal.length <= 2 * 104
// 	s and goal consist of lowercase letters.
//

class Solution {
public:
    bool buddyStrings(string s, string goal) {
        if (s.length() != goal.length()) {
            return false;
        }

        if (s == goal) {
            vector<int> count(26, 0);
            for (char c : s) {
                count[c - 'a']++;
                if (count[c - 'a'] > 1) {
                    return true;
                }
            }
            return false;
        }

        vector<int> diffIndices;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] != goal[i]) {
                diffIndices.push_back(i);
            }
        }

        if (diffIndices.size() != 2) {
            return false;
        }

        return s[diffIndices[0]] == goal[diffIndices[1]] &&
               s[diffIndices[1]] == goal[diffIndices[0]];           
    }
};
