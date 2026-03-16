// Source: https://leetcode.com/problems/redistribute-characters-to-make-all-strings-equal/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of strings words (0-indexed).
//
// In one operation, pick two distinct indices i and j, where words[i] is a non-empty string, and move any character from words[i] to any position in words[j].
//
// Return true if you can make every string in words equal using any number of operations, and false otherwise.
//
// Example:
// Input: words = ["abc","aabc","bc"]
// Output: true
// Explanation: Move the first 'a' in words[1] to the front of words[2],
// to make words[1] = "abc" and words[2] = "abc".
// All the strings are now equal to "abc", so return true.
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 100
// 	words[i] consists of lowercase English letters.
//

class Solution {
public:
    bool makeEqual(vector<string>& words) {
        vector<int> charCount(26, 0);
        int totalChars = 0;

        // Count the frequency of each character across all strings
        for (const string& word : words) {
            for (char c : word) {
                charCount[c - 'a']++;
                totalChars++;
            }
        }

        int n = words.size();
        // Check if each character's count is divisible by the number of strings
        for (int count : charCount) {
            if (count % n != 0) {
                return false;
            }
        }

        return true;            
    }
};
