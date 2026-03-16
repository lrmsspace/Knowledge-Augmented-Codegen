// Source: https://leetcode.com/problems/apply-operations-to-make-string-empty/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s.
//
// Consider performing the following operation until s becomes empty:
//
//
// 	For every alphabet character from 'a' to 'z', remove the first occurrence of that character in s (if it exists).
//
//
// For example, let initially s = "aabcbbca". We do the following operations:
//
//
// 	Remove the underlined characters s = "aabcbbca". The resulting string is s = "abbca".
// 	Remove the underlined characters s = "abbca". The resulting string is s = "ba".
// 	Remove the underlined characters s = "ba". The resulting string is s = "".
//
//
// Return the value of the string s right before applying the last operation. In the example above, answer is "ba".
//
// Example:
// Input: s = "aabcbbca"
// Output: "ba"
// Explanation: Explained in the statement.
//
// Constraints:
// 1 <= s.length <= 5 * 105
// 	s consists only of lowercase English letters.
//

class Solution {
public:
    string lastNonEmptyString(string s) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        string result;
        for (char c : s) {
            if (count[c - 'a'] > 1) {
                count[c - 'a']--;
            } else {
                result += c;
            }
        }

        return result;          
    }
};
