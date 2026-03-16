// Source: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.
//
// Example:
// Input: s = "bcabc"
// Output: "abc"
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase English letters.
//
//
//  
// Note: This question is the same as 316: https://leetcode.com/problems/remove-duplicate-letters/
//

class Solution {
public:
    string smallestSubsequence(string s) {
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
