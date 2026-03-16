// Source: https://leetcode.com/problems/find-common-characters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string array words, return an array of all characters that show up in all strings within the words (including duplicates). You may return the answer in any order.
//
// Example:
// Input: words = ["bella","label","roller"]
// Output: ["e","l","l"]
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 100
// 	words[i] consists of lowercase English letters.
//

class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        vector<int> minFreq(26, INT_MAX);
        for (const string& word : words) {
            vector<int> freq(26, 0);
            for (char c : word) {
                freq[c - 'a']++;
            }
            for (int i = 0; i < 26; ++i) {
                minFreq[i] = min(minFreq[i], freq[i]);
            }
        }

        vector<string> result;
        for (int i = 0; i < 26; ++i) {
            while (minFreq[i] > 0) {
                result.push_back(string(1, 'a' + i));
                minFreq[i]--;
            }
        }

        return result;          
    }
};
