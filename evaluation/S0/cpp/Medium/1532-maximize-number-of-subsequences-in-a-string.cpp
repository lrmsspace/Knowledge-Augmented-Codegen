// Source: https://leetcode.com/problems/maximize-number-of-subsequences-in-a-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string text and another 0-indexed string pattern of length 2, both of which consist of only lowercase English letters.
//
// You can add either pattern[0] or pattern[1] anywhere in text exactly once. Note that the character can be added even at the beginning or at the end of text.
//
// Return the maximum number of times pattern can occur as a subsequence of the modified text.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// Example:
// Input: text = "abdcdbc", pattern = "ac"
// Output: 4
// Explanation:
// If we add pattern[0] = 'a' in between text[1] and text[2], we get "abadcdbc". Now, the number of times "ac" occurs as a subsequence is 4.
// Some other strings which have 4 subsequences "ac" after adding a character to text are "aabdcdbc" and "abdacdbc".
// However, strings such as "abdcadbc", "abdccdbc", and "abdcdbcc", although obtainable, have only 3 subsequences "ac" and are thus suboptimal.
// It can be shown that it is not possible to get more than 4 subsequences "ac" by adding only one character.
//
// Constraints:
// 1 <= text.length <= 105
// 	pattern.length == 2
// 	text and pattern consist only of lowercase English letters.
//

class Solution {
public:
    long long maximumSubsequenceCount(string text, string pattern) {
        long long countFirst = 0;
        long long countSecond = 0;
        long long totalPairs = 0;

        for (char c : text) {
            if (c == pattern[1]) {
                totalPairs += countFirst;
                countSecond++;
            }
            if (c == pattern[0]) {
                countFirst++;
            }
        }

        // Consider adding pattern[0] at the beginning
        long long option1 = totalPairs + countSecond;

        // Consider adding pattern[1] at the end
        long long option2 = totalPairs + countFirst;

        return max(option1, option2);           
    }
};
