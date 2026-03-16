// Source: https://leetcode.com/problems/find-words-containing-character/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array of strings words and a character x.
//
// Return an array of indices representing the words that contain the character x.
//
// Note that the returned array may be in any order.
//
// Example:
// Input: words = ["leet","code"], x = "e"
// Output: [0,1]
// Explanation: "e" occurs in both words: "leet", and "code". Hence, we return indices 0 and 1.
//
// Constraints:
// 1 <= words.length <= 50
// 	1 <= words[i].length <= 50
// 	x is a lowercase English letter.
// 	words[i] consists only of lowercase English letters.
//

class Solution {
public:
    vector<int> findWordsContaining(vector<string>& words, char x) {
        vector<int> result;
        for (int i = 0; i < words.size(); ++i) {
            if (words[i].find(x) != string::npos) {
                result.push_back(i);
            }
        }
        return result;          
    }
};
