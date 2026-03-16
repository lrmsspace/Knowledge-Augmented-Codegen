// Source: https://leetcode.com/problems/unique-length-3-palindromic-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the number of unique palindromes of length three that are a subsequence of s.
//
// Note that even if there are multiple ways to obtain the same subsequence, it is still only counted once.
//
// A palindrome is a string that reads the same forwards and backwards.
//
// A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
//
//
// 	For example, "ace" is a subsequence of "abcde".
//
// Example:
// Input: s = "aabca"
// Output: 3
// Explanation: The 3 palindromic subsequences of length 3 are:
// - "aba" (subsequence of "aabca")
// - "aaa" (subsequence of "aabca")
// - "aca" (subsequence of "aabca")
//
// Constraints:
// 3 <= s.length <= 105
// 	s consists of only lowercase English letters.
//

class Solution {
public:
    int countPalindromicSubsequence(string s) {
        vector<vector<int>> charIndices(26);
        for (int i = 0; i < s.size(); ++i) {
            charIndices[s[i] - 'a'].push_back(i);
        }

        unordered_set<string> uniquePalindromes;
        for (int i = 0; i < 26; ++i) {
            const auto& indices = charIndices[i];
            if (indices.size() < 2) continue;

            for (int j = 0; j < 26; ++j) {
                if (j == i) continue;

                // Check if there's any occurrence of character j between the first and last occurrence of character i
                auto it = lower_bound(indices.begin(), indices.end(), indices.front() + 1);
                if (it != indices.end() && *it < indices.back()) {
                    uniquePalindromes.insert(string(1, 'a' + i) + string(1, 'a' + j) + string(1, 'a' + i));
                }
            }
        }

        return uniquePalindromes.size();            
    }
};
