// Source: https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/   |   Difficulty: Medium
//
// Problem Description:
// A string is considered beautiful if it satisfies the following conditions:
//
//
// 	Each of the 5 English vowels ('a', 'e', 'i', 'o', 'u') must appear at least once in it.
// 	The letters must be sorted in alphabetical order (i.e. all 'a's before 'e's, all 'e's before 'i's, etc.).
//
//
// For example, strings "aeiou" and "aaaaaaeiiiioou" are considered beautiful, but "uaeio", "aeoiu", and "aaaeeeooo" are not beautiful.
//
// Given a string word consisting of English vowels, return the length of the longest beautiful substring of word. If no such substring exists, return 0.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: word = "aeiaaioaaaaeiiiiouuuooaauuaeiu"
// Output: 13
// Explanation: The longest beautiful substring in word is "aaaaeiiiiouuu" of length 13.
//
// Constraints:
// 1 <= word.length <= 5 * 105
// 	word consists of characters 'a', 'e', 'i', 'o', and 'u'.
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
    int longestBeautifulSubstring(string word) {
        int n = (int)word.size();
        int maxLen = 0;
        int i = 0;
        while (i < n) {
            if (word[i] != 'a') {
                i++;
                continue;
            }
            int j = i;
            int vowelIdx = 0; // 0:'a',1:'e',2:'i',3:'o',4:'u'
            while (j < n) {
                char c = word[j];
                if (c == 'a' && vowelIdx == 0) {
                    j++;
                } else if (c == 'e' && vowelIdx <= 1) {
                    vowelIdx = 1;
                    j++;
                } else if (c == 'i' && vowelIdx <= 2) {
                    vowelIdx = 2;
                    j++;
                } else if (c == 'o' && vowelIdx <= 3) {
                    vowelIdx = 3;
                    j++;
                } else if (c == 'u' && vowelIdx <= 4) {
                    vowelIdx = 4;
                    j++;
                } else {
                    break;
                }
            }
            if (vowelIdx == 4) { // found all vowels
                int len = j - i;
                if (len > maxLen) {
                    maxLen = len;
                }
            }
            i = j;
        }
        return maxLen;          
    }
};
