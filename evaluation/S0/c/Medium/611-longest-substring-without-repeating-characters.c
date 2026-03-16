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

int lengthOfLongestSubstring(char* s) {
    int n = strlen(s);
    int maxLength = 0;
    int charIndex[128] = {0}; // ASCII character set

    int left = 0; // Left pointer of the sliding window
    for (int right = 0; right < n; right++) {
        char currentChar = s[right];
        // If the character has been seen and is within the current window
        if (charIndex[(int)currentChar] > left) {
            left = charIndex[(int)currentChar];
        }
        // Update the last seen index of the current character
        charIndex[(int)currentChar] = right + 1; // Store index + 1 to differentiate from default 0
        // Update maxLength if we found a longer substring
        int currentLength = right - left + 1;
        if (currentLength > maxLength) {
            maxLength = currentLength;
        }
    }

    return maxLength;       
}
