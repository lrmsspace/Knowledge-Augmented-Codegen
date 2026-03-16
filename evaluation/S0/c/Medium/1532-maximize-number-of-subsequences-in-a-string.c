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

long long maximumSubsequenceCount(char* text, char* pattern) {
    long long count_first = 0, count_second = 0, total = 0;
    char first_char = pattern[0], second_char = pattern[1];

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == second_char) {
            total += count_first;
            count_second++;
        }
        if (text[i] == first_char) {
            count_first++;
        }
    }

    long long option1 = total + count_second; // Adding first_char
    long long option2 = total + count_first;  // Adding second_char

    return option1 > option2 ? option1 : option2;       
}
