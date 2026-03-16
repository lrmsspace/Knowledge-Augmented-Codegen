// Source: https://leetcode.com/problems/decrypt-string-from-alphabet-to-integer-mapping/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s formed by digits and '#'. We want to map s to English lowercase characters as follows:
//
//
// 	Characters ('a' to 'i') are represented by ('1' to '9') respectively.
// 	Characters ('j' to 'z') are represented by ('10#' to '26#') respectively.
//
//
// Return the string formed after mapping.
//
// The test cases are generated so that a unique mapping will always exist.
//
// Example:
// Input: s = "10#11#12"
// Output: "jkab"
// Explanation: "j" -> "10#" , "k" -> "11#" , "a" -> "1" , "b" -> "2".
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of digits and the '#' letter.
// 	s will be a valid string such that mapping is always possible.
//

class Solution {
public:
    string freqAlphabets(string s) {
        string result;
        for (int i = 0; i < s.size(); ++i) {
            if (i + 2 < s.size() && s[i + 2] == '#') {
                int num = (s[i] - '0') * 10 + (s[i + 1] - '0');
                result += static_cast<char>('a' + num - 1);
                i += 2;
            } else {
                int num = s[i] - '0';
                result += static_cast<char>('a' + num - 1);
            }
        }
        return result;          
    }
};
