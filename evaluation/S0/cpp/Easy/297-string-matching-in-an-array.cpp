// Source: https://leetcode.com/problems/string-matching-in-an-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of string words, return all strings in words that are a substring of another word. You can return the answer in any order.
//
// Example:
// Input: words = ["mass","as","hero","superhero"]
// Output: ["as","hero"]
// Explanation: "as" is substring of "mass" and "hero" is substring of "superhero".
// ["hero","as"] is also a valid answer.
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 30
// 	words[i] contains only lowercase English letters.
// 	All the strings of words are unique.
//

class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        vector<string> result;
        int n = words.size();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && words[j].find(words[i]) != string::npos) {
                    result.push_back(words[i]);
                    break;
                }
            }
        }

        return result;          
    }
};
