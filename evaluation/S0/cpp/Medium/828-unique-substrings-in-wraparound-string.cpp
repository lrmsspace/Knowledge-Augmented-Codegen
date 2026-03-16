// Source: https://leetcode.com/problems/unique-substrings-in-wraparound-string/   |   Difficulty: Medium
//
// Problem Description:
// We define the string base to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so base will look like this:
//
//
// 	"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
//
//
// Given a string s, return the number of unique non-empty substrings of s are present in base.
//
// Example:
// Input: s = "a"
// Output: 1
// Explanation: Only the substring "a" of s is in base.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
//

class Solution {
public:
    int findSubstringInWraproundString(string s) {
        vector<int> count(26, 0);
        int maxLength = 0;

        for (int i = 0; i < s.length(); ++i) {
            if (i > 0 && (s[i] - s[i - 1] + 26) % 26 == 1) {
                maxLength++;
            } else {
                maxLength = 1;
            }
            int index = s[i] - 'a';
            count[index] = max(count[index], maxLength);
        }

        int result = 0;
        for (int c : count) {
            result += c;
        }
        return result;          
    }
};
