// Source: https://leetcode.com/problems/remove-duplicate-letters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
//
// Example:
// Input: s = "bcabc"
// Output: "abc"
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of lowercase English letters.
//
//
//  
// Note: This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
//

class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> lastIndex(26, -1);
        for (int i = 0; i < s.size(); ++i) {
            lastIndex[s[i] - 'a'] = i;
        }

        vector<bool> inResult(26, false);
        string result;
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (inResult[c - 'a']) {
                continue;
            }

            while (!result.empty() && result.back() > c && lastIndex[result.back() - 'a'] > i) {
                inResult[result.back() - 'a'] = false;
                result.pop_back();
            }

            result.push_back(c);
            inResult[c - 'a'] = true;
        }

        return result;          
    }
};
