// Source: https://leetcode.com/problems/print-words-vertically/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s. Return all the words vertically in the same order in which they appear in s.
// Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
// Each word would be put on only one column and that in one column there will be only one word.
//
// Example:
// Input: s = "HOW ARE YOU"
// Output: ["HAY","ORO","WEU"]
// Explanation: Each word is printed vertically. 
//  "HAY"
//  "ORO"
//  "WEU"
//
// Constraints:
// 1 <= s.length <= 200
// 	s contains only upper case English letters.
// 	It's guaranteed that there is only one space between 2 words.
//

class Solution {
public:
    vector<string> printVertically(string s) {
        vector<string> words;
        int maxLen = 0;
        size_t pos = 0, found;
        while ((found = s.find_first_of(' ', pos)) != string::npos) {
            string word = s.substr(pos, found - pos);
            words.push_back(word);
            maxLen = max(maxLen, (int)word.length());
            pos = found + 1;
        }
        // Last word
        string word = s.substr(pos);
        words.push_back(word);
        maxLen = max(maxLen, (int)word.length());

        vector<string> result;
        for (int col = 0; col < maxLen; ++col) {
            string verticalWord;
            for (const string& w : words) {
                if (col < w.length()) {
                    verticalWord += w[col];
                } else {
                    verticalWord += ' ';
                }
            }
            // Trim trailing spaces
            size_t endpos = verticalWord.find_last_not_of(' ');
            if (endpos != string::npos) {
                verticalWord = verticalWord.substr(0, endpos + 1);
            }
            result.push_back(verticalWord);
        }

        return result;          
    }
};
