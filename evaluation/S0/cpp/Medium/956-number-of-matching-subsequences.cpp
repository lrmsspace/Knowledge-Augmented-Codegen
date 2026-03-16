// Source: https://leetcode.com/problems/number-of-matching-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an array of strings words, return the number of words[i] that is a subsequence of s.
//
// A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
//
//
// 	For example, "ace" is a subsequence of "abcde".
//
// Example:
// Input: s = "abcde", words = ["a","bb","acd","ace"]
// Output: 3
// Explanation: There are three strings in words that are a subsequence of s: "a", "acd", "ace".
//
// Constraints:
// 1 <= s.length <= 5 * 104
// 	1 <= words.length <= 5000
// 	1 <= words[i].length <= 50
// 	s and words[i] consist of only lowercase English letters.
//

class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        unordered_map<char, vector<int>> charIndices;
        for (int i = 0; i < s.size(); ++i) {
            charIndices[s[i]].push_back(i);
        }

        int matchingCount = 0;

        for (const string& word : words) {
            int prevIndex = -1;
            bool isSubsequence = true;

            for (char c : word) {
                if (charIndices.find(c) == charIndices.end()) {
                    isSubsequence = false;
                    break;
                }

                const vector<int>& indices = charIndices[c];
                auto it = upper_bound(indices.begin(), indices.end(), prevIndex);
                if (it == indices.end()) {
                    isSubsequence = false;
                    break;
                }

                prevIndex = *it;
            }

            if (isSubsequence) {
                ++matchingCount;
            }
        }

        return matchingCount;           
    }
};
