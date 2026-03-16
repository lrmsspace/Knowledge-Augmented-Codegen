// Source: https://leetcode.com/problems/keyboard-row/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below.
//
// Note that the strings are case-insensitive, both lowercased and uppercased of the same letter are treated as if they are at the same row.
//
// In the American keyboard:
//
//
// 	the first row consists of the characters "qwertyuiop",
// 	the second row consists of the characters "asdfghjkl", and
// 	the third row consists of the characters "zxcvbnm".
//
// Example:
// Input: words = ["Hello","Alaska","Dad","Peace"]
//
// Output: ["Alaska","Dad"]
//
// Explanation:
//
// Both "a" and "A" are in the 2nd row of the American keyboard due to case insensitivity.
//
// Constraints:
// 1 <= words.length <= 20
// 	1 <= words[i].length <= 100
// 	words[i] consists of English letters (both lowercase and uppercase).
//

class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        vector<string> result;
        unordered_map<char, int> charToRow = {
            {'q', 0}, {'w', 0}, {'e', 0}, {'r', 0}, {'t', 0}, {'y', 0}, {'u', 0}, {'i', 0}, {'o', 0}, {'p', 0},
            {'a', 1}, {'s', 1}, {'d', 1}, {'f', 1}, {'g', 1}, {'h', 1}, {'j', 1}, {'k', 1}, {'l', 1},
            {'z', 2}, {'x', 2}, {'c', 2}, {'v', 2}, {'b', 2}, {'n', 2}, {'m', 2}
        };

        for (const string& word : words) {
            int row = charToRow[tolower(word[0])];
            bool canBeTyped = true;

            for (char c : word) {
                if (charToRow[tolower(c)] != row) {
                    canBeTyped = false;
                    break;
                }
            }

            if (canBeTyped) {
                result.push_back(word);
            }
        }

        return result;          
    }
};
