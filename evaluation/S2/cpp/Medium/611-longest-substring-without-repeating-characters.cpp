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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> charSet;
        int left = 0, right = 0, maxLength = 0;

        while (right < s.length()) {
            if (charSet.find(s[right]) == charSet.end()) {
                // Character not in set, add it and update max length
                charSet.insert(s[right]);
                maxLength = max(maxLength, right - left + 1);
                right++;
            } else {
                // Character already in set, remove the leftmost character and move left pointer
                charSet.erase(s[left]);
                left++;
            }
        }

        return maxLength;           
    }
};
