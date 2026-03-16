// Source: https://leetcode.com/problems/word-pattern/   |   Difficulty: Easy
//
// Problem Description:
// Given a pattern and a string s, find if s follows the same pattern.
//
// Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in s. Specifically:
//
//
// 	Each letter in pattern maps to exactly one unique word in s.
// 	Each unique word in s maps to exactly one letter in pattern.
// 	No two letters map to the same word, and no two words map to the same letter.
//
// Example:
// Input: pattern = "abba", s = "dog cat cat dog"
//
// Output: true
//
// Explanation:
//
// The bijection can be established as:
//
//
// 	'a' maps to "dog".
// 	'b' maps to "cat".
//
// Constraints:
// 1 <= pattern.length <= 300
// 	pattern contains only lower-case English letters.
// 	1 <= s.length <= 3000
// 	s contains only lowercase English letters and spaces ' '.
// 	s does not contain any leading or trailing spaces.
// 	All the words in s are separated by a single space.
//

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        unordered_map<char, string> p2s;
        unordered_map<string, char> s2p;

        istringstream iss(s);
        string word;
        int index = 0;

        while (iss >> word) {
            if (index >= pattern.size()) {
                return false; // More words than pattern letters
            }

            char pChar = pattern[index];

            // Check mapping from pattern to string
            if (p2s.count(pChar)) {
                if (p2s[pChar] != word) {
                    return false; // Mismatch in mapping
                }
            } else {
                p2s[pChar] = word;
            }

            // Check mapping from string to pattern
            if (s2p.count(word)) {
                if (s2p[word] != pChar) {
                    return false; // Mismatch in mapping
                }
            } else {
                s2p[word] = pChar;
            }

            index++;
        }

        return index == pattern.size(); // Ensure all pattern letters are used          
    }
};
