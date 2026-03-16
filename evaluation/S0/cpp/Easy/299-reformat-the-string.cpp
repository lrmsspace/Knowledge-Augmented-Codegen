// Source: https://leetcode.com/problems/reformat-the-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given an alphanumeric string s. (Alphanumeric string is a string consisting of lowercase English letters and digits).
//
// You have to find a permutation of the string where no letter is followed by another letter and no digit is followed by another digit. That is, no two adjacent characters have the same type.
//
// Return the reformatted string or return an empty string if it is impossible to reformat the string.
//
// Example:
// Input: s = "a0b1c2"
// Output: "0a1b2c"
// Explanation: No two adjacent characters have the same type in "0a1b2c". "a0b1c2", "0a1b2c", "0c2a1b" are also valid permutations.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of only lowercase English letters and/or digits.
//

class Solution {
public:
    string reformat(string s) {
        string letters, digits;
        for (char c : s) {
            if (isdigit(c)) {
                digits.push_back(c);
            } else {
                letters.push_back(c);
            }
        }

        int lenL = letters.length();
        int lenD = digits.length();

        if (abs(lenL - lenD) > 1) {
            return "";
        }

        string result;
        bool letterTurn = lenL >= lenD;

        int i = 0, j = 0;
        while (i < lenL || j < lenD) {
            if (letterTurn && i < lenL) {
                result.push_back(letters[i++]);
            } else if (!letterTurn && j < lenD) {
                result.push_back(digits[j++]);
            }
            letterTurn = !letterTurn;
        }

        return result;          
    }
};
