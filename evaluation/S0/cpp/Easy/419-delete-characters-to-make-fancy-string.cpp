// Source: https://leetcode.com/problems/delete-characters-to-make-fancy-string/   |   Difficulty: Easy
//
// Problem Description:
// A fancy string is a string where no three consecutive characters are equal.
//
// Given a string s, delete the minimum possible number of characters from s to make it fancy.
//
// Return the final string after the deletion. It can be shown that the answer will always be unique.
//
// Example:
// Input: s = "leeetcode"
// Output: "leetcode"
// Explanation:
// Remove an 'e' from the first group of 'e's to create "leetcode".
// No three consecutive characters are equal, so return "leetcode".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters.
//

class Solution {
public:
    string makeFancyString(string s) {
        string result;
        int count = 1;

        for (size_t i = 0; i < s.size(); ++i) {
            if (i > 0 && s[i] == s[i - 1]) {
                count++;
            } else {
                count = 1;
            }

            if (count < 3) {
                result += s[i];
            }
        }

        return result;          
    }
};
