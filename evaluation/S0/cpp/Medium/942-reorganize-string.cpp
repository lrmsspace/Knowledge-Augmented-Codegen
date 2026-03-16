// Source: https://leetcode.com/problems/reorganize-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.
//
// Return any possible rearrangement of s or return "" if not possible.
//
// Example:
// Input: s = "aab"
// Output: "aba"
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of lowercase English letters.
//

class Solution {
public:
    string reorganizeString(string s) {
        vector<int> count(26, 0);
        int maxCount = 0;
        for (char c : s) {
            count[c - 'a']++;
            maxCount = max(maxCount, count[c - 'a']);
        }

        if (maxCount > (s.length() + 1) / 2) {
            return "";
        }

        string result(s.length(), ' ');
        int index = 0;

        for (int i = 0; i < 26; ++i) {
            while (count[i] > 0 && count[i] <= (s.length() / 2) && index < s.length()) {
                result[index] = 'a' + i;
                index += 2;
                count[i]--;
            }
        }

        for (int i = 0; i < 26; ++i) {
            while (count[i] > 0) {
                if (index >= s.length()) {
                    index = 1;
                }
                result[index] = 'a' + i;
                index += 2;
                count[i]--;
            }
        }

        return result;          
    }
};
