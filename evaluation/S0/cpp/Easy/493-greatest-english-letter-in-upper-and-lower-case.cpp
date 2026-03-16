// Source: https://leetcode.com/problems/greatest-english-letter-in-upper-and-lower-case/   |   Difficulty: Easy
//
// Problem Description:
// Given a string of English letters s, return the greatest English letter which occurs as both a lowercase and uppercase letter in s. The returned letter should be in uppercase. If no such letter exists, return an empty string.
//
// An English letter b is greater than another letter a if b appears after a in the English alphabet.
//
// Example:
// Input: s = "lEeTcOdE"
// Output: "E"
// Explanation:
// The letter 'E' is the only letter to appear in both lower and upper case.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase and uppercase English letters.
//

class Solution {
public:
    string greatestLetter(string s) {
        vector<bool> lower(26, false);
        vector<bool> upper(26, false);

        for (char c : s) {
            if (islower(c)) {
                lower[c - 'a'] = true;
            } else {
                upper[c - 'A'] = true;
            }
        }

        for (int i = 25; i >= 0; --i) {
            if (lower[i] && upper[i]) {
                return string(1, 'A' + i);
            }
        }

        return "";          
    }
};
