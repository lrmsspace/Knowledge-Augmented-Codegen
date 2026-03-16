// Source: https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings words. Each element of words consists of two lowercase English letters.
//
// Create the longest possible palindrome by selecting some elements from words and concatenating them in any order. Each element can be selected at most once.
//
// Return the length of the longest palindrome that you can create. If it is impossible to create any palindrome, return 0.
//
// A palindrome is a string that reads the same forward and backward.
//
// Example:
// Input: words = ["lc","cl","gg"]
// Output: 6
// Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
// Note that "clgglc" is another longest palindrome that can be created.
//
// Constraints:
// 1 <= words.length <= 105
// 	words[i].length == 2
// 	words[i] consists of lowercase English letters.
//

class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        unordered_map<string, int> countMap;
        for (const auto& word : words) {
            countMap[word]++;
        }

        int length = 0;
        bool hasOddCenter = false;

        for (const auto& [word, count] : countMap) {
            string reversedWord = string(1, word[1]) + string(1, word[0]);
            if (word == reversedWord) {
                // Word is a palindrome itself (e.g., "gg")
                length += (count / 2) * 4; // Each pair contributes 4 to the length
                if (count % 2 == 1) {
                    hasOddCenter = true; // We can place one odd palindrome in the center
                }
            } else if (countMap.find(reversedWord) != countMap.end()) {
                // Word has a reverse counterpart (e.g., "lc" and "cl")
                int pairs = min(count, countMap[reversedWord]);
                length += pairs * 4; // Each pair contributes 4 to the length
                // To avoid double counting, set the count of the reversed word to 0
                countMap[reversedWord] = 0;
            }
        }

        if (hasOddCenter) {
            length += 2; // Add 2 for the center palindrome
        }

        return length;          
    }
};
