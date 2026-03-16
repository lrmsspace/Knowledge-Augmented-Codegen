// Source: https://leetcode.com/problems/longest-string-chain/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of words where each word consists of lowercase English letters.
//
// wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB.
//
//
// 	For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
//
//
// A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain with k == 1.
//
// Return the length of the longest possible word chain with words chosen from the given list of words.
//
// Example:
// Input: words = ["a","b","ba","bca","bda","bdca"]
// Output: 4
// Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 16
// 	words[i] only consists of lowercase English letters.
//

class Solution {
public:
    int longestStrChain(vector<string>& words) {
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.length() < b.length();
        });

        unordered_map<string, int> dp;
        int maxLength = 1;

        for (const string& word : words) {
            dp[word] = 1; // Minimum chain length is 1 (the word itself)

            for (size_t i = 0; i < word.length(); ++i) {
                string predecessor = word.substr(0, i) + word.substr(i + 1);
                if (dp.find(predecessor) != dp.end()) {
                    dp[word] = max(dp[word], dp[predecessor] + 1);
                }
            }

            maxLength = max(maxLength, dp[word]);
        }

        return maxLength;           
    }
};
