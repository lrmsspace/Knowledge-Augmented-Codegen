// Source: https://leetcode.com/problems/longest-word-in-dictionary/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings words representing an English Dictionary, return the longest word in words that can be built one character at a time by other words in words.
//
// If there is more than one possible answer, return the longest word with the smallest lexicographical order. If there is no answer, return the empty string.
//
// Note that the word should be built from left to right with each additional character being added to the end of a previous word.
//
// Example:
// Input: words = ["w","wo","wor","worl","world"]
// Output: "world"
// Explanation: The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 30
// 	words[i] consists of lowercase English letters.
//

class Solution {
public:
    string longestWord(vector<string>& words) {
        unordered_set<string> wordSet(words.begin(), words.end());
        string result = "";

        for (const string& word : words) {
            if (word.length() < result.length() || 
               (word.length() == result.length() && word > result)) {
                continue;
            }

            bool canBuild = true;
            for (int k = 1; k < word.length(); ++k) {
                if (wordSet.find(word.substr(0, k)) == wordSet.end()) {
                    canBuild = false;
                    break;
                }
            }

            if (canBuild) {
                result = word;
            }
        }

        return result;          
    }
};
