// Source: https://leetcode.com/problems/longest-substring-without-repeating-characters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, find the length of the longest substring without duplicate characters.
//
// Example:
// Input: s = "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.
//
// Constraints:
// 0 <= s.length <= 5 * 104
// 	s consists of English letters, digits, symbols and spaces.
//

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> charSet;
        int left = 0, right = 0;
        int maxLength = 0;

        while (right < s.length()) {
            if (charSet.find(s[right]) == charSet.end()) {
                charSet.insert(s[right]);
                maxLength = max(maxLength, right - left + 1);
                right++;
            } else {
                charSet.erase(s[left]);
                left++;
            }
        }

        return maxLength;           
    }
};
